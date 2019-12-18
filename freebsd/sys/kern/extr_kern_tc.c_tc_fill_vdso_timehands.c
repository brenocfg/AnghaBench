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
typedef  scalar_t__ uint32_t ;
struct vdso_timehands {int /*<<< orphan*/  th_boottime; int /*<<< orphan*/  th_offset; int /*<<< orphan*/  th_counter_mask; int /*<<< orphan*/  th_offset_count; int /*<<< orphan*/  th_scale; } ;
struct timehands {TYPE_1__* th_counter; int /*<<< orphan*/  th_boottime; int /*<<< orphan*/  th_offset; int /*<<< orphan*/  th_offset_count; int /*<<< orphan*/  th_scale; } ;
struct TYPE_2__ {scalar_t__ (* tc_fill_vdso_timehands ) (struct vdso_timehands*,TYPE_1__*) ;int /*<<< orphan*/  tc_counter_mask; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct vdso_timehands*,TYPE_1__*) ; 
 struct timehands* timehands ; 
 int /*<<< orphan*/  vdso_th_enable ; 

uint32_t
tc_fill_vdso_timehands(struct vdso_timehands *vdso_th)
{
	struct timehands *th;
	uint32_t enabled;

	th = timehands;
	vdso_th->th_scale = th->th_scale;
	vdso_th->th_offset_count = th->th_offset_count;
	vdso_th->th_counter_mask = th->th_counter->tc_counter_mask;
	vdso_th->th_offset = th->th_offset;
	vdso_th->th_boottime = th->th_boottime;
	if (th->th_counter->tc_fill_vdso_timehands != NULL) {
		enabled = th->th_counter->tc_fill_vdso_timehands(vdso_th,
		    th->th_counter);
	} else
		enabled = 0;
	if (!vdso_th_enable)
		enabled = 0;
	return (enabled);
}