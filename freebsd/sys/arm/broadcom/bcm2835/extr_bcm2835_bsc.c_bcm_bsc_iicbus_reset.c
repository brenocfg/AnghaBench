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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct bcm_bsc_softc {int /*<<< orphan*/ * sc_iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_BSC_CLOCK ; 
 int BCM_BSC_CORE_CLK ; 
 int /*<<< orphan*/  BCM_BSC_LOCK (struct bcm_bsc_softc*) ; 
 int /*<<< orphan*/  BCM_BSC_UNLOCK (struct bcm_bsc_softc*) ; 
 int /*<<< orphan*/  BCM_BSC_WRITE (struct bcm_bsc_softc*,int /*<<< orphan*/ ,int) ; 
 int IICBUS_GET_FREQUENCY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IIC_ENOADDR ; 
 int /*<<< orphan*/  bcm_bsc_reset (struct bcm_bsc_softc*) ; 
 struct bcm_bsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_bsc_iicbus_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct bcm_bsc_softc *sc;
	uint32_t busfreq;

	sc = device_get_softc(dev);
	BCM_BSC_LOCK(sc);
	bcm_bsc_reset(sc);
	if (sc->sc_iicbus == NULL)
		busfreq = 100000;
	else
		busfreq = IICBUS_GET_FREQUENCY(sc->sc_iicbus, speed);
	BCM_BSC_WRITE(sc, BCM_BSC_CLOCK, BCM_BSC_CORE_CLK / busfreq);
	BCM_BSC_UNLOCK(sc);

	return (IIC_ENOADDR);
}