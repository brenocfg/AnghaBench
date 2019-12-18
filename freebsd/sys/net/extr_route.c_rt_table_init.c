#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* rnh_masks; } ;
struct TYPE_3__ {int /*<<< orphan*/  mask_nodes; TYPE_2__ head; } ;
struct rib_head {int /*<<< orphan*/  rnh_walktree_from; int /*<<< orphan*/  rnh_walktree; int /*<<< orphan*/  rnh_lookup; int /*<<< orphan*/  rnh_matchaddr; int /*<<< orphan*/  rnh_deladdr; int /*<<< orphan*/  rnh_addaddr; TYPE_1__ rmhead; TYPE_2__ head; int /*<<< orphan*/  rnh_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RTABLE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RIB_LOCK_INIT (struct rib_head*) ; 
 struct rib_head* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rn_addroute ; 
 int /*<<< orphan*/  rn_delete ; 
 int /*<<< orphan*/  rn_inithead_internal (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rn_lookup ; 
 int /*<<< orphan*/  rn_match ; 
 int /*<<< orphan*/  rn_walktree ; 
 int /*<<< orphan*/  rn_walktree_from ; 

struct rib_head *
rt_table_init(int offset)
{
	struct rib_head *rh;

	rh = malloc(sizeof(struct rib_head), M_RTABLE, M_WAITOK | M_ZERO);

	/* TODO: These details should be hidded inside radix.c */
	/* Init masks tree */
	rn_inithead_internal(&rh->head, rh->rnh_nodes, offset);
	rn_inithead_internal(&rh->rmhead.head, rh->rmhead.mask_nodes, 0);
	rh->head.rnh_masks = &rh->rmhead;

	/* Init locks */
	RIB_LOCK_INIT(rh);

	/* Finally, set base callbacks */
	rh->rnh_addaddr = rn_addroute;
	rh->rnh_deladdr = rn_delete;
	rh->rnh_matchaddr = rn_match;
	rh->rnh_lookup = rn_lookup;
	rh->rnh_walktree = rn_walktree;
	rh->rnh_walktree_from = rn_walktree_from;

	return (rh);
}