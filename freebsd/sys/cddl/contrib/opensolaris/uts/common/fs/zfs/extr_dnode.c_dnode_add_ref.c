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
struct TYPE_3__ {int /*<<< orphan*/  dn_mtx; int /*<<< orphan*/  dn_holds; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

boolean_t
dnode_add_ref(dnode_t *dn, void *tag)
{
	mutex_enter(&dn->dn_mtx);
	if (zfs_refcount_is_zero(&dn->dn_holds)) {
		mutex_exit(&dn->dn_mtx);
		return (FALSE);
	}
	VERIFY(1 < zfs_refcount_add(&dn->dn_holds, tag));
	mutex_exit(&dn->dn_mtx);
	return (TRUE);
}