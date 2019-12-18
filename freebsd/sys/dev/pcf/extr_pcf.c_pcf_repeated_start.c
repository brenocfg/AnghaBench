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
typedef  scalar_t__ u_char ;
struct pcf_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ACK ; 
 struct pcf_softc* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int ESO ; 
 int IIC_ENOACK ; 
 int /*<<< orphan*/  PCF_LOCK (struct pcf_softc*) ; 
 int /*<<< orphan*/  PCF_UNLOCK (struct pcf_softc*) ; 
 int STA ; 
 int STO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ pcf_noack (struct pcf_softc*,int) ; 
 int /*<<< orphan*/  pcf_set_S0 (struct pcf_softc*,scalar_t__) ; 
 int /*<<< orphan*/  pcf_set_S1 (struct pcf_softc*,int) ; 
 int /*<<< orphan*/  pcf_stop_locked (struct pcf_softc*) ; 
 int pcf_wait_byte (struct pcf_softc*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
pcf_repeated_start(device_t dev, u_char slave, int timeout)
{
	struct pcf_softc *sc = DEVTOSOFTC(dev);
	int error = 0;

	PCF_LOCK(sc);
#ifdef PCFDEBUG
	device_printf(dev, " >> repeated start for slave %#x\n",
		      (unsigned)slave);
#endif
	/* repeated start */
	pcf_set_S1(sc, ESO|STA|STO|ACK);

	/* set slave address to PCF. Last bit (LSB) must be set correctly
	 * according to transfer direction */
	pcf_set_S0(sc, slave);

	/* wait for address sent, polling */
	if ((error = pcf_wait_byte(sc)))
		goto error;

	/* check for ack */
	if (pcf_noack(sc, timeout)) {
		error = IIC_ENOACK;
#ifdef PCFDEBUG
		printf("pcf: no ack on repeated_start!\n");
#endif
		goto error;
	}

	PCF_UNLOCK(sc);
	return (0);

error:
	pcf_stop_locked(sc);
	PCF_UNLOCK(sc);
	return (error);
}