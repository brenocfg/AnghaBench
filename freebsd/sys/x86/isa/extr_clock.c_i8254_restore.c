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
struct TYPE_2__ {int /*<<< orphan*/  period; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_STOP ; 
 TYPE_1__* attimer_sc ; 
 int /*<<< orphan*/  set_i8254_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timer0_last ; 
 int timer0_mode ; 
 int timer0_period ; 

__attribute__((used)) static void
i8254_restore(void)
{

	timer0_period = -2;
	timer0_mode = 0xffff;
	timer0_last = 0xffff;
	if (attimer_sc != NULL)
		set_i8254_freq(attimer_sc->mode, attimer_sc->period);
	else
		set_i8254_freq(MODE_STOP, 0);
}