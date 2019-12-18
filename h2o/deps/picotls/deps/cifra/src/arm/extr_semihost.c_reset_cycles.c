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
struct TYPE_2__ {int ctrl; scalar_t__ current; int /*<<< orphan*/  reload; } ;

/* Variables and functions */
 int STCTRL_ENABLE ; 
 int /*<<< orphan*/  STCTRL_MAX ; 
 int STCTRL_SYSCLOCK ; 
 int STCTRL_TICKINT ; 
 TYPE_1__* SysTick ; 
 int /*<<< orphan*/  get_ticks () ; 
 int /*<<< orphan*/  reset_ticks () ; 

uint32_t reset_cycles(void)
{
  SysTick->reload = STCTRL_MAX;
  SysTick->ctrl = STCTRL_SYSCLOCK | STCTRL_TICKINT | STCTRL_ENABLE;
  SysTick->current = 0;
  reset_ticks();
  return get_ticks();
}