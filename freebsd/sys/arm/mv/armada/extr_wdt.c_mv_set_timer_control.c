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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  wdt_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TIMER_CONTROL ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* wdt_softc ; 

__attribute__((used)) static __inline void
mv_set_timer_control(uint32_t val)
{

	bus_write_4(wdt_softc->wdt_res, CPU_TIMER_CONTROL, val);
}