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
struct zyd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_MAC_TX_PE_CONTROL ; 
 int /*<<< orphan*/  zyd_read32_m (struct zyd_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  zyd_write32_m (struct zyd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zyd_set_led(struct zyd_softc *sc, int which, int on)
{
	int error;
	uint32_t tmp;

	zyd_read32_m(sc, ZYD_MAC_TX_PE_CONTROL, &tmp);
	tmp &= ~which;
	if (on)
		tmp |= which;
	zyd_write32_m(sc, ZYD_MAC_TX_PE_CONTROL, tmp);
fail:
	return (error);
}