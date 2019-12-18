#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ ms_weight; int /*<<< orphan*/  ms_group; scalar_t__ ms_activation_weight; int /*<<< orphan*/  ms_allocatable; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 scalar_t__ METASLAB_ACTIVE_MASK ; 
 scalar_t__ METASLAB_WEIGHT_TYPE ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  metaslab_passivate_allocator (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ range_tree_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metaslab_passivate(metaslab_t *msp, uint64_t weight)
{
	uint64_t size = weight & ~METASLAB_WEIGHT_TYPE;

	/*
	 * If size < SPA_MINBLOCKSIZE, then we will not allocate from
	 * this metaslab again.  In that case, it had better be empty,
	 * or we would be leaving space on the table.
	 */
	ASSERT(size >= SPA_MINBLOCKSIZE ||
	    range_tree_is_empty(msp->ms_allocatable));
	ASSERT0(weight & METASLAB_ACTIVE_MASK);

	msp->ms_activation_weight = 0;
	metaslab_passivate_allocator(msp->ms_group, msp, weight);
	ASSERT((msp->ms_weight & METASLAB_ACTIVE_MASK) == 0);
}