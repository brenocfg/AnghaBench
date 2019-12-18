#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ offset_t ;
struct TYPE_8__ {scalar_t__ f_offset; struct TYPE_8__* f_vnode; } ;
typedef  TYPE_2__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 scalar_t__ MAXOFFSET_T ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_write_rights ; 
 int /*<<< orphan*/  curthread ; 
 int dmu_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  fget_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_2__* getf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releasef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_diff(zfs_cmd_t *zc)
{
	file_t *fp;
	offset_t off;
	int error;

#ifdef illumos
	fp = getf(zc->zc_cookie);
#else
	fget_write(curthread, zc->zc_cookie, &cap_write_rights, &fp);
#endif
	if (fp == NULL)
		return (SET_ERROR(EBADF));

	off = fp->f_offset;

#ifdef illumos
	error = dmu_diff(zc->zc_name, zc->zc_value, fp->f_vnode, &off);
#else
	error = dmu_diff(zc->zc_name, zc->zc_value, fp, &off);
#endif

	if (off >= 0 && off <= MAXOFFSET_T)
		fp->f_offset = off;
	releasef(zc->zc_cookie);

	return (error);
}