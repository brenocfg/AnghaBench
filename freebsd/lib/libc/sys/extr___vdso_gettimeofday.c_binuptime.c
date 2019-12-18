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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct vdso_timekeep {scalar_t__ tk_current; struct vdso_timehands* tk_th; int /*<<< orphan*/  tk_enabled; } ;
struct bintime {int dummy; } ;
struct vdso_timehands {scalar_t__ th_gen; int th_scale; int /*<<< orphan*/  th_boottime; struct bintime th_offset; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSYS ; 
 scalar_t__ atomic_load_acq_32 (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  bintime_add (struct bintime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_addx (struct bintime*,int) ; 
 int tc_delta (struct vdso_timehands*,int*) ; 

__attribute__((used)) static int
binuptime(struct bintime *bt, struct vdso_timekeep *tk, int abs)
{
	struct vdso_timehands *th;
	uint32_t curr, gen;
	u_int delta;
	int error;

	do {
		if (!tk->tk_enabled)
			return (ENOSYS);

		curr = atomic_load_acq_32(&tk->tk_current);
		th = &tk->tk_th[curr];
		gen = atomic_load_acq_32(&th->th_gen);
		*bt = th->th_offset;
		error = tc_delta(th, &delta);
		if (error == EAGAIN)
			continue;
		if (error != 0)
			return (error);
		bintime_addx(bt, th->th_scale * delta);
		if (abs)
			bintime_add(bt, &th->th_boottime);

		/*
		 * Ensure that the load of th_offset is completed
		 * before the load of th_gen.
		 */
		atomic_thread_fence_acq();
	} while (curr != tk->tk_current || gen == 0 || gen != th->th_gen);
	return (0);
}