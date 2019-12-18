#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_5__ {int /*<<< orphan*/ * vfs_data; } ;
typedef  TYPE_1__ vfs_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int getzfsvfs_impl (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int vfs_busy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_rel (TYPE_1__*) ; 

int
getzfsvfs(const char *dsname, zfsvfs_t **zfvp)
{
	objset_t *os;
	vfs_t *vfsp;
	int error;

	error = dmu_objset_hold(dsname, FTAG, &os);
	if (error != 0)
		return (error);
	error = getzfsvfs_impl(os, &vfsp);
	dmu_objset_rele(os, FTAG);
	if (error != 0)
		return (error);

	error = vfs_busy(vfsp, 0);
	vfs_rel(vfsp);
	if (error != 0) {
		*zfvp = NULL;
		error = SET_ERROR(ESRCH);
	} else {
		*zfvp = vfsp->vfs_data;
	}
	return (error);
}