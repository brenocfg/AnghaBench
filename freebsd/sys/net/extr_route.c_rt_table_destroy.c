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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct rib_head {TYPE_1__ rmhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RTABLE ; 
 int /*<<< orphan*/  RIB_LOCK_DESTROY (struct rib_head*) ; 
 int /*<<< orphan*/  free (struct rib_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rn_walktree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_freeentry ; 

void
rt_table_destroy(struct rib_head *rh)
{

	rn_walktree(&rh->rmhead.head, rt_freeentry, &rh->rmhead.head);

	/* Assume table is already empty */
	RIB_LOCK_DESTROY(rh);
	free(rh, M_RTABLE);
}