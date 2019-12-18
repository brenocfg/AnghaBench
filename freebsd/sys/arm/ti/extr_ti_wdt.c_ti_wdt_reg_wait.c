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
struct ti_wdt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  TI_WDT_WWPS ; 
 int ti_wdt_reg_read (struct ti_wdt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ti_wdt_reg_wait(struct ti_wdt_softc *sc, uint32_t bit)
{

	while (ti_wdt_reg_read(sc, TI_WDT_WWPS) & bit)
		DELAY(10);
}