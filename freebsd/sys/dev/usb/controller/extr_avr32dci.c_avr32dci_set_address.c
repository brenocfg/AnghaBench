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
typedef  int uint8_t ;
struct avr32dci_softc {int dummy; } ;

/* Variables and functions */
 int AVR32_CTRL_DEV_FADDR_EN ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int /*<<< orphan*/  avr32dci_mod_ctrl (struct avr32dci_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
avr32dci_set_address(struct avr32dci_softc *sc, uint8_t addr)
{
	DPRINTFN(5, "addr=%d\n", addr);

	avr32dci_mod_ctrl(sc, AVR32_CTRL_DEV_FADDR_EN | addr, 0);
}