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
typedef  int time64_t ;
struct eeh_pe {scalar_t__ freeze_count; int tstamp; } ;

/* Variables and functions */
 void* ktime_get_seconds () ; 

void eeh_pe_update_time_stamp(struct eeh_pe *pe)
{
	time64_t tstamp;

	if (!pe) return;

	if (pe->freeze_count <= 0) {
		pe->freeze_count = 0;
		pe->tstamp = ktime_get_seconds();
	} else {
		tstamp = ktime_get_seconds();
		if (tstamp - pe->tstamp > 3600) {
			pe->tstamp = tstamp;
			pe->freeze_count = 0;
		}
	}
}