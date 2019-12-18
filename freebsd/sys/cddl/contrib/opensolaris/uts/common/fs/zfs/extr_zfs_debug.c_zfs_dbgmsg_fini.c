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
struct TYPE_4__ {int /*<<< orphan*/  zdm_msg; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int zfs_dbgmsg_size ; 
 int /*<<< orphan*/  zfs_dbgmsgs ; 
 int /*<<< orphan*/  zfs_dbgmsgs_lock ; 

void
zfs_dbgmsg_fini(void)
{
	zfs_dbgmsg_t *zdm;

	while ((zdm = list_remove_head(&zfs_dbgmsgs)) != NULL) {
		int size = sizeof (zfs_dbgmsg_t) + strlen(zdm->zdm_msg);
		kmem_free(zdm, size);
		zfs_dbgmsg_size -= size;
	}
	mutex_destroy(&zfs_dbgmsgs_lock);
	ASSERT0(zfs_dbgmsg_size);
}