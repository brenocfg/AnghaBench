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
struct siis_channel {int /*<<< orphan*/  r_mem; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIIS_P_CTLCLR ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int /*<<< orphan*/  SIIS_P_CTL_LED_ON ; 
 struct siis_channel* device_get_softc (scalar_t__) ; 

__attribute__((used)) static void
siis_ch_led(void *priv, int onoff)
{
	device_t dev;
	struct siis_channel *ch;

	dev = (device_t)priv;
	ch = device_get_softc(dev);

	if (onoff == 0)
		ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_LED_ON);
	else
		ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_LED_ON);
}