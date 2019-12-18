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
struct throtl_grp {unsigned long* slice_start; scalar_t__* slice_end; int /*<<< orphan*/  service_queue; TYPE_1__* td; scalar_t__* io_disp; scalar_t__* bytes_disp; } ;
struct TYPE_2__ {scalar_t__ throtl_slice; } ;

/* Variables and functions */
 int READ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  throtl_log (int /*<<< orphan*/ *,char*,char,unsigned long,scalar_t__,scalar_t__) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void throtl_start_new_slice_with_credit(struct throtl_grp *tg,
		bool rw, unsigned long start)
{
	tg->bytes_disp[rw] = 0;
	tg->io_disp[rw] = 0;

	/*
	 * Previous slice has expired. We must have trimmed it after last
	 * bio dispatch. That means since start of last slice, we never used
	 * that bandwidth. Do try to make use of that bandwidth while giving
	 * credit.
	 */
	if (time_after_eq(start, tg->slice_start[rw]))
		tg->slice_start[rw] = start;

	tg->slice_end[rw] = jiffies + tg->td->throtl_slice;
	throtl_log(&tg->service_queue,
		   "[%c] new slice with credit start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', tg->slice_start[rw],
		   tg->slice_end[rw], jiffies);
}