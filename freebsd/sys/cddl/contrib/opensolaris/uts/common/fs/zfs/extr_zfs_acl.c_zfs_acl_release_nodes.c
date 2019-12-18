#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ z_acl_bytes; scalar_t__ z_acl_count; int /*<<< orphan*/  z_acl; } ;
typedef  TYPE_1__ zfs_acl_t ;
typedef  int /*<<< orphan*/  zfs_acl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_acl_node_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfs_acl_release_nodes(zfs_acl_t *aclp)
{
	zfs_acl_node_t *aclnode;

	while (aclnode = list_head(&aclp->z_acl)) {
		list_remove(&aclp->z_acl, aclnode);
		zfs_acl_node_free(aclnode);
	}
	aclp->z_acl_count = 0;
	aclp->z_acl_bytes = 0;
}