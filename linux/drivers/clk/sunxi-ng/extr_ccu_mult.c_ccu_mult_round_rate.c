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
struct clk_hw {int dummy; } ;
struct ccu_mux_internal {int dummy; } ;
struct TYPE_2__ {int width; scalar_t__ offset; scalar_t__ max; int /*<<< orphan*/  min; } ;
struct ccu_mult {TYPE_1__ mult; } ;
struct _ccu_mult {unsigned long mult; scalar_t__ max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_mult_find_best (unsigned long,unsigned long,struct _ccu_mult*) ; 

__attribute__((used)) static unsigned long ccu_mult_round_rate(struct ccu_mux_internal *mux,
					 struct clk_hw *parent,
					 unsigned long *parent_rate,
					 unsigned long rate,
					 void *data)
{
	struct ccu_mult *cm = data;
	struct _ccu_mult _cm;

	_cm.min = cm->mult.min;

	if (cm->mult.max)
		_cm.max = cm->mult.max;
	else
		_cm.max = (1 << cm->mult.width) + cm->mult.offset - 1;

	ccu_mult_find_best(*parent_rate, rate, &_cm);

	return *parent_rate * _cm.mult;
}