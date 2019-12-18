#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcf_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pcf_softc* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESO ; 
 int /*<<< orphan*/  PCF_LOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  PCF_UNLOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dummy_read (struct pcf_softc*) ; 
 int /*<<< orphan*/  pcf_get_S0 (struct pcf_softc*) ; 
 int /*<<< orphan*/  pcf_set_S1 (struct pcf_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf_stop_locked (struct pcf_softc*) ; 
 int pcf_wait_byte (struct pcf_softc*) ; 

int
pcf_read(device_t dev, char *buf, int len, int *read, int last,
	 int delay /* us */)
{
	struct pcf_softc *sc = DEVTOSOFTC(dev);
	int bytes, error = 0;
#ifdef PCFDEBUG
	char *obuf = buf;

	device_printf(dev, " << reading %d bytes\n", len);
#endif

	PCF_LOCK(sc);
	/* trig the bus to get the first data byte in S0 */
	if (len) {
		if (len == 1 && last)
			/* just one byte to read */
			pcf_set_S1(sc, ESO);		/* no ack */

		dummy_read(sc);
	}

	bytes = 0;
	while (len) {

		/* XXX delay needed here */

		/* wait for trigged byte */
		if ((error = pcf_wait_byte(sc))) {
			pcf_stop_locked(sc);
			goto error;
		}

		if (len == 1 && last)
			/* ok, last data byte already in S0, no I2C activity
			 * on next pcf_get_S0() */
			pcf_stop_locked(sc);

		else if (len == 2 && last)
			/* next trigged byte with no ack */
			pcf_set_S1(sc, ESO);

		/* receive byte, trig next byte */
		*buf++ = pcf_get_S0(sc);

		len --;
		bytes ++;
	}

error:
	*read = bytes;
	PCF_UNLOCK(sc);

#ifdef PCFDEBUG
	device_printf(dev, " << %d bytes read (%d): %#x%s\n", bytes, error,
		      (unsigned)obuf[0], bytes > 1? "...": "");
#endif

	return (error);
}