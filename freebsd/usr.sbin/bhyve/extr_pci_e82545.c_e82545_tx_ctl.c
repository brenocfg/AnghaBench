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
struct e82545_softc {int esc_tx_enabled; int esc_TCTL; int /*<<< orphan*/ * esc_txdesc; scalar_t__ esc_tdba; } ;

/* Variables and functions */
 int E1000_TCTL_EN ; 
 int /*<<< orphan*/  e82545_tx_disable (struct e82545_softc*) ; 
 int /*<<< orphan*/  e82545_tx_enable (struct e82545_softc*) ; 
 int /*<<< orphan*/  e82545_tx_update_tdba (struct e82545_softc*) ; 

__attribute__((used)) static void
e82545_tx_ctl(struct e82545_softc *sc, uint32_t val)
{
	int on;
	
	on = ((val & E1000_TCTL_EN) == E1000_TCTL_EN);

	/* ignore TCTL_EN settings that don't change state */
	if (on == sc->esc_tx_enabled)
		return;

	if (on) {
		e82545_tx_update_tdba(sc);
		e82545_tx_enable(sc);
	} else {
		e82545_tx_disable(sc);
		sc->esc_tdba = 0;
		sc->esc_txdesc = NULL;
	}

	/* Save TCTL value after stripping reserved bits 31:25,23,2,0 */
	sc->esc_TCTL = val & ~0xFE800005;
}