#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  bpo_lock; TYPE_1__* bpo_phys; scalar_t__ bpo_havecomp; } ;
typedef  TYPE_2__ bpobj_t ;
struct TYPE_6__ {int /*<<< orphan*/  bpo_uncomp; int /*<<< orphan*/  bpo_comp; int /*<<< orphan*/  bpo_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  bpobj_is_open (TYPE_2__*) ; 
 int bpobj_space_range (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

int
bpobj_space(bpobj_t *bpo, uint64_t *usedp, uint64_t *compp, uint64_t *uncompp)
{
	ASSERT(bpobj_is_open(bpo));
	mutex_enter(&bpo->bpo_lock);

	*usedp = bpo->bpo_phys->bpo_bytes;
	if (bpo->bpo_havecomp) {
		*compp = bpo->bpo_phys->bpo_comp;
		*uncompp = bpo->bpo_phys->bpo_uncomp;
		mutex_exit(&bpo->bpo_lock);
		return (0);
	} else {
		mutex_exit(&bpo->bpo_lock);
		return (bpobj_space_range(bpo, 0, UINT64_MAX,
		    usedp, compp, uncompp));
	}
}