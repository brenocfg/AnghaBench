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
struct vop_vptofh_args {scalar_t__ a_fhp; int /*<<< orphan*/  a_vp; } ;
struct udf_node {int /*<<< orphan*/  hash_id; } ;
struct ifid {int ifid_len; int /*<<< orphan*/  ifid_ino; } ;

/* Variables and functions */
 struct udf_node* VTON (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udf_vptofh(struct vop_vptofh_args *a)
{
	struct udf_node *node;
	struct ifid *ifhp;

	node = VTON(a->a_vp);
	ifhp = (struct ifid *)a->a_fhp;
	ifhp->ifid_len = sizeof(struct ifid);
	ifhp->ifid_ino = node->hash_id;

	return (0);
}