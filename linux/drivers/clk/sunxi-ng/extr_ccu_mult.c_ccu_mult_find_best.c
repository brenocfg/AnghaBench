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
struct _ccu_mult {int min; int max; int mult; } ;

/* Variables and functions */

__attribute__((used)) static void ccu_mult_find_best(unsigned long parent, unsigned long rate,
			       struct _ccu_mult *mult)
{
	int _mult;

	_mult = rate / parent;
	if (_mult < mult->min)
		_mult = mult->min;

	if (_mult > mult->max)
		_mult = mult->max;

	mult->mult = _mult;
}