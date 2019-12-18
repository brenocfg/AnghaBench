#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ period; scalar_t__ period_factor; } ;

/* Variables and functions */
 scalar_t__ nitems (TYPE_1__*) ; 
 TYPE_1__* scsi_syncrates ; 

u_int
scsi_calc_syncparam(u_int period)
{
	u_int i;
	u_int num_syncrates;

	if (period == 0)
		return (~0);	/* Async */

	/* Adjust for exception table being in 100ths. */
	period *= 10;
	num_syncrates = nitems(scsi_syncrates);
	/* See if the period is in the "exception" table */
	for (i = 0; i < num_syncrates; i++) {

		if (period <= scsi_syncrates[i].period) {
			/* Period in 100ths of ns */
			return (scsi_syncrates[i].period_factor);
		}
	}

	/*
	 * Wasn't in the table, so use the standard
	 * 1/4 period in ns conversion.
	 */
	return (period/400);
}