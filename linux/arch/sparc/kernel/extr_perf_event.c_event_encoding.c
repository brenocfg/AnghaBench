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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  lower_shift; int /*<<< orphan*/  upper_shift; } ;

/* Variables and functions */
 int PIC_UPPER_INDEX ; 
 TYPE_1__* sparc_pmu ; 

__attribute__((used)) static u64 event_encoding(u64 event_id, int idx)
{
	if (idx == PIC_UPPER_INDEX)
		event_id <<= sparc_pmu->upper_shift;
	else
		event_id <<= sparc_pmu->lower_shift;
	return event_id;
}