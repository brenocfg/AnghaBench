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
struct vop_vptofh_args {int /*<<< orphan*/  a_vp; scalar_t__ a_fhp; } ;
struct tmpfs_node {int /*<<< orphan*/  tn_gen; int /*<<< orphan*/  tn_id; } ;
struct tmpfs_fid {int tf_len; int /*<<< orphan*/  tf_gen; int /*<<< orphan*/  tf_id; } ;

/* Variables and functions */
 struct tmpfs_node* VP_TO_TMPFS_NODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmpfs_vptofh(struct vop_vptofh_args *ap)
{
	struct tmpfs_fid *tfhp;
	struct tmpfs_node *node;

	tfhp = (struct tmpfs_fid *)ap->a_fhp;
	node = VP_TO_TMPFS_NODE(ap->a_vp);

	tfhp->tf_len = sizeof(struct tmpfs_fid);
	tfhp->tf_id = node->tn_id;
	tfhp->tf_gen = node->tn_gen;

	return (0);
}