#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct asmc_softc {int sc_sms_intr_works; scalar_t__ sc_nfan; TYPE_1__* sc_model; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * smc_sms_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASMC_DPRINTF (char*) ; 
 int /*<<< orphan*/  ASMC_KEY_INTOK ; 
 int /*<<< orphan*/  ASMC_KEY_SMS ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_FLAG ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_HIGH ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_HIGH_INT ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_LOW ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_LOW_INT ; 
 scalar_t__ ASMC_MAXFANS ; 
 int /*<<< orphan*/  ASMC_NKEYS ; 
 int ASMC_SMS_INIT1 ; 
 int ASMC_SMS_INIT2 ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  asmc_dumpall (int /*<<< orphan*/ ) ; 
 scalar_t__ asmc_fan_count (int /*<<< orphan*/ ) ; 
 scalar_t__ asmc_key_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  asmc_key_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  asmc_sms_calibrate (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 struct asmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
asmc_init(device_t dev)
{
	struct asmc_softc *sc = device_get_softc(dev);
	int i, error = 1;
	uint8_t buf[4];

	if (sc->sc_model->smc_sms_x == NULL)
		goto nosms;

	/*
	 * We are ready to receive interrupts from the SMS.
	 */
	buf[0] = 0x01;
	ASMC_DPRINTF(("intok key\n"));
	asmc_key_write(dev, ASMC_KEY_INTOK, buf, 1);
	DELAY(50);

	/*
	 * Initiate the polling intervals.
	 */
	buf[0] = 20; /* msecs */
	ASMC_DPRINTF(("low int key\n"));
	asmc_key_write(dev, ASMC_KEY_SMS_LOW_INT, buf, 1);
	DELAY(200);

	buf[0] = 20; /* msecs */
	ASMC_DPRINTF(("high int key\n"));
	asmc_key_write(dev, ASMC_KEY_SMS_HIGH_INT, buf, 1);
	DELAY(200);

	buf[0] = 0x00;
	buf[1] = 0x60;
	ASMC_DPRINTF(("sms low key\n"));
	asmc_key_write(dev, ASMC_KEY_SMS_LOW, buf, 2);
	DELAY(200);

	buf[0] = 0x01;
	buf[1] = 0xc0;
	ASMC_DPRINTF(("sms high key\n"));
	asmc_key_write(dev, ASMC_KEY_SMS_HIGH, buf, 2);
	DELAY(200);

	/*
	 * I'm not sure what this key does, but it seems to be
	 * required.
	 */
	buf[0] = 0x01;
	ASMC_DPRINTF(("sms flag key\n"));
	asmc_key_write(dev, ASMC_KEY_SMS_FLAG, buf, 1);
	DELAY(100);

	sc->sc_sms_intr_works = 0;

	/*
	 * Retry SMS initialization 1000 times
	 * (takes approx. 2 seconds in worst case)
	 */
	for (i = 0; i < 1000; i++) {
		if (asmc_key_read(dev, ASMC_KEY_SMS, buf, 2) == 0 &&
		    (buf[0] == ASMC_SMS_INIT1 && buf[1] == ASMC_SMS_INIT2)) {
			error = 0;
			sc->sc_sms_intr_works = 1;
			goto out;
		}
		buf[0] = ASMC_SMS_INIT1;
		buf[1] = ASMC_SMS_INIT2;
		ASMC_DPRINTF(("sms key\n"));
		asmc_key_write(dev, ASMC_KEY_SMS, buf, 2);
		DELAY(50);
	}
	device_printf(dev, "WARNING: Sudden Motion Sensor not initialized!\n");

out:
	asmc_sms_calibrate(dev);
nosms:
	sc->sc_nfan = asmc_fan_count(dev);
	if (sc->sc_nfan > ASMC_MAXFANS) {
		device_printf(dev, "more than %d fans were detected. Please "
		    "report this.\n", ASMC_MAXFANS);
		sc->sc_nfan = ASMC_MAXFANS;
	}

	if (bootverbose) {
		/*
		 * The number of keys is a 32 bit buffer
		 */
		asmc_key_read(dev, ASMC_NKEYS, buf, 4);
		device_printf(dev, "number of keys: %d\n", ntohl(*(uint32_t*)buf));
	}

#ifdef DEBUG
	asmc_dumpall(dev);
#endif

	return (error);
}