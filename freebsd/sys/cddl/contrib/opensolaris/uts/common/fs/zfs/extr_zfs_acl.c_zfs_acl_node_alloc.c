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
struct TYPE_4__ {size_t z_allocsize; size_t z_size; int /*<<< orphan*/  z_acldata; int /*<<< orphan*/  z_allocdata; } ;
typedef  TYPE_1__ zfs_acl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

zfs_acl_node_t *
zfs_acl_node_alloc(size_t bytes)
{
	zfs_acl_node_t *aclnode;

	aclnode = kmem_zalloc(sizeof (zfs_acl_node_t), KM_SLEEP);
	if (bytes) {
		aclnode->z_acldata = kmem_alloc(bytes, KM_SLEEP);
		aclnode->z_allocdata = aclnode->z_acldata;
		aclnode->z_allocsize = bytes;
		aclnode->z_size = bytes;
	}

	return (aclnode);
}