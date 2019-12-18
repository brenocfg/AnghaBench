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
struct throtl_grp {int /*<<< orphan*/ * slice_end; int /*<<< orphan*/ * slice_start; int /*<<< orphan*/  service_queue; TYPE_1__* td; } ;
struct TYPE_2__ {int /*<<< orphan*/  throtl_slice; } ;

/* Variables and functions */
 int READ ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  roundup (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throtl_log (int /*<<< orphan*/ *,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void throtl_extend_slice(struct throtl_grp *tg, bool rw,
				       unsigned long jiffy_end)
{
	tg->slice_end[rw] = roundup(jiffy_end, tg->td->throtl_slice);
	throtl_log(&tg->service_queue,
		   "[%c] extend slice start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', tg->slice_start[rw],
		   tg->slice_end[rw], jiffies);
}