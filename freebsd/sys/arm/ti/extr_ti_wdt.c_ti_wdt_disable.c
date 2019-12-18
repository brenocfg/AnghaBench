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
struct ti_wdt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ti_wdt_softc*) ; 
 int /*<<< orphan*/  TI_WDT_WSPR ; 
 int /*<<< orphan*/  TI_W_PEND_WSPR ; 
 int /*<<< orphan*/  ti_wdt_reg_wait (struct ti_wdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_wdt_reg_write (struct ti_wdt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
ti_wdt_disable(struct ti_wdt_softc *sc)
{

	DPRINTF("disabling watchdog %p\n", sc);
	ti_wdt_reg_write(sc, TI_WDT_WSPR, 0xAAAA);
	ti_wdt_reg_wait(sc, TI_W_PEND_WSPR);
	ti_wdt_reg_write(sc, TI_WDT_WSPR, 0x5555);
	ti_wdt_reg_wait(sc, TI_W_PEND_WSPR);
}