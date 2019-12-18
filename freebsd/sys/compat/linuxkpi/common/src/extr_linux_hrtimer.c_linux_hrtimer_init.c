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
struct hrtimer {int /*<<< orphan*/  mtx; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_NOWITNESS ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hrtimer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

void
linux_hrtimer_init(struct hrtimer *hrtimer)
{

	memset(hrtimer, 0, sizeof(*hrtimer));
	mtx_init(&hrtimer->mtx, "hrtimer", NULL,
	    MTX_DEF | MTX_RECURSE | MTX_NOWITNESS);
	callout_init_mtx(&hrtimer->callout, &hrtimer->mtx, 0);
}