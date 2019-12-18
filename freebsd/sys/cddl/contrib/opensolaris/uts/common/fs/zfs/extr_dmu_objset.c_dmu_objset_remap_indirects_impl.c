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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int EEXIST ; 
 int ENOENT ; 
 int ESRCH ; 
 int dmu_object_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmu_object_remap_indirects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmu_objset_remap_indirects_impl(objset_t *os, uint64_t last_removed_txg)
{
	int error = 0;
	uint64_t object = 0;
	while ((error = dmu_object_next(os, &object, B_FALSE, 0)) == 0) {
		error = dmu_object_remap_indirects(os, object,
		    last_removed_txg);
		/*
		 * If the ZPL removed the object before we managed to dnode_hold
		 * it, we would get an ENOENT. If the ZPL declares its intent
		 * to remove the object (dnode_free) before we manage to
		 * dnode_hold it, we would get an EEXIST. In either case, we
		 * want to continue remapping the other objects in the objset;
		 * in all other cases, we want to break early.
		 */
		if (error != 0 && error != ENOENT && error != EEXIST) {
			break;
		}
	}
	if (error == ESRCH) {
		error = 0;
	}
	return (error);
}