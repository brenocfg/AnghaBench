#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  arcs_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  arcs_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_BUFC_METADATA ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arc_adjust_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* arc_anon ; 
 scalar_t__ arc_c ; 
 scalar_t__ arc_meta_limit ; 
 TYPE_1__* arc_mfu ; 
 TYPE_1__* arc_mru ; 
 scalar_t__ arc_p ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
arc_adjust_meta_only(uint64_t meta_used)
{
	uint64_t total_evicted = 0;
	int64_t target;

	/*
	 * If we're over the meta limit, we want to evict enough
	 * metadata to get back under the meta limit. We don't want to
	 * evict so much that we drop the MRU below arc_p, though. If
	 * we're over the meta limit more than we're over arc_p, we
	 * evict some from the MRU here, and some from the MFU below.
	 */
	target = MIN((int64_t)(meta_used - arc_meta_limit),
	    (int64_t)(zfs_refcount_count(&arc_anon->arcs_size) +
	    zfs_refcount_count(&arc_mru->arcs_size) - arc_p));

	total_evicted += arc_adjust_impl(arc_mru, 0, target, ARC_BUFC_METADATA);

	/*
	 * Similar to the above, we want to evict enough bytes to get us
	 * below the meta limit, but not so much as to drop us below the
	 * space allotted to the MFU (which is defined as arc_c - arc_p).
	 */
	target = MIN((int64_t)(meta_used - arc_meta_limit),
	    (int64_t)(zfs_refcount_count(&arc_mfu->arcs_size) -
	    (arc_c - arc_p)));

	total_evicted += arc_adjust_impl(arc_mfu, 0, target, ARC_BUFC_METADATA);

	return (total_evicted);
}