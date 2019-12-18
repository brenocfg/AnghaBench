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
 int TI_IRQ_EV_DLY ; 
 int TI_IRQ_EV_OVF ; 
 int /*<<< orphan*/  TI_WDT_WIRQSTAT ; 
 int /*<<< orphan*/  ti_wdt_reg_write (struct ti_wdt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ti_wdt_intr(void *arg)
{
	struct ti_wdt_softc *sc;

	sc = arg;
	DPRINTF("interrupt %p", sc);
	ti_wdt_reg_write(sc, TI_WDT_WIRQSTAT, TI_IRQ_EV_OVF | TI_IRQ_EV_DLY);
	/* TODO: handle interrupt */
}