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
struct sysc {int /*<<< orphan*/  rsts; } ;

/* Variables and functions */
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_rstctrl_reset_deassert(struct sysc *ddata, bool reset)
{
	int error;

	if (!ddata->rsts)
		return 0;

	if (reset) {
		error = reset_control_assert(ddata->rsts);
		if (error)
			return error;
	}

	reset_control_deassert(ddata->rsts);

	return 0;
}