#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  wdt_res; } ;

/* Variables and functions */
 scalar_t__ CPU_TIMER0 ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_1__* wdt_softc ; 

__attribute__((used)) static __inline void
mv_set_timer(uint32_t timer, uint32_t val)
{

	bus_write_4(wdt_softc->wdt_res, CPU_TIMER0 + timer * 0x8, val);
}