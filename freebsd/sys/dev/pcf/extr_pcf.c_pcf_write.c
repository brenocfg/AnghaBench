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
 int IIC_ENOACK ; 
 int /*<<< orphan*/  PCF_LOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  PCF_UNLOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ pcf_noack (struct pcf_softc*,int) ; 
 int /*<<< orphan*/  pcf_set_S0 (struct pcf_softc*,int /*<<< orphan*/ ) ; 
 int pcf_wait_byte (struct pcf_softc*) ; 

int
pcf_write(device_t dev, const char *buf, int len, int *sent, int timeout /* us */)
{
	struct pcf_softc *sc = DEVTOSOFTC(dev);
	int bytes, error = 0;

#ifdef PCFDEBUG
	device_printf(dev, " >> writing %d bytes: %#x%s\n", len,
		      (unsigned)buf[0], len > 1? "...": "");
#endif

	bytes = 0;
	PCF_LOCK(sc);
	while (len) {

		pcf_set_S0(sc, *buf++);

		/* wait for the byte to be send */
		if ((error = pcf_wait_byte(sc)))
			goto error;

		/* check if ack received */
		if (pcf_noack(sc, timeout)) {
			error = IIC_ENOACK;
			goto error;
		}

		len --;
		bytes ++;
	}

error:
	*sent = bytes;
	PCF_UNLOCK(sc);

#ifdef PCFDEBUG
	device_printf(dev, " >> %d bytes written (%d)\n", bytes, error);
#endif

	return (error);
}