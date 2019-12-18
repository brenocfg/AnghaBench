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
struct throtl_grp {TYPE_1__* td; int /*<<< orphan*/ * slice_end; } ;
struct TYPE_2__ {int /*<<< orphan*/  throtl_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  roundup (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void throtl_set_slice_end(struct throtl_grp *tg, bool rw,
					unsigned long jiffy_end)
{
	tg->slice_end[rw] = roundup(jiffy_end, tg->td->throtl_slice);
}