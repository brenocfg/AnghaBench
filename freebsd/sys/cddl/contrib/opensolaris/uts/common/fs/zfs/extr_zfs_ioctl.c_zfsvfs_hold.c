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
struct TYPE_5__ {scalar_t__ z_unmounted; int /*<<< orphan*/  z_teardown_lock; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ getzfsvfs (char const*,TYPE_1__**) ; 
 int /*<<< orphan*/  rrm_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rrm_exit (int /*<<< orphan*/ *,void*) ; 
 int zfsvfs_create (char const*,TYPE_1__**) ; 

__attribute__((used)) static int
zfsvfs_hold(const char *name, void *tag, zfsvfs_t **zfvp, boolean_t writer)
{
	int error = 0;

	if (getzfsvfs(name, zfvp) != 0)
		error = zfsvfs_create(name, zfvp);
	if (error == 0) {
		rrm_enter(&(*zfvp)->z_teardown_lock, (writer) ? RW_WRITER :
		    RW_READER, tag);
#ifdef illumos
		if ((*zfvp)->z_unmounted) {
			/*
			 * XXX we could probably try again, since the unmounting
			 * thread should be just about to disassociate the
			 * objset from the zfsvfs.
			 */
			rrm_exit(&(*zfvp)->z_teardown_lock, tag);
			return (SET_ERROR(EBUSY));
		}
#else
		/*
		 * vfs_busy() ensures that the filesystem is not and
		 * can not be unmounted.
		 */
		ASSERT(!(*zfvp)->z_unmounted);
#endif
	}
	return (error);
}