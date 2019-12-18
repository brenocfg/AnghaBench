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
struct unionfs_node_status {scalar_t__ uns_lower_opencnt; scalar_t__ uns_upper_opencnt; } ;
struct unionfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct unionfs_node_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  UNIONFSTOV (struct unionfs_node*) ; 
 int /*<<< orphan*/  free (struct unionfs_node_status*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uns_list ; 

void
unionfs_tryrem_node_status(struct unionfs_node *unp,
			   struct unionfs_node_status *unsp)
{
	KASSERT(NULL != unsp, ("null pointer"));
	ASSERT_VOP_ELOCKED(UNIONFSTOV(unp), "unionfs_get_node_status");

	if (0 < unsp->uns_lower_opencnt || 0 < unsp->uns_upper_opencnt)
		return;

	LIST_REMOVE(unsp, uns_list);
	free(unsp, M_TEMP);
}