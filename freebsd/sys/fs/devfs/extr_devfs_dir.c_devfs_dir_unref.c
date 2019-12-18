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
struct dirlistent {scalar_t__ refcnt; struct dirlistent* dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct dirlistent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVFS4 ; 
 struct dirlistent* devfs_dir_findent_locked (char const*) ; 
 int /*<<< orphan*/  dirlist_mtx ; 
 int /*<<< orphan*/  free (struct dirlistent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devfs_dir_unref(const char *dir)
{
	struct dirlistent *dle;

	if (*dir == '\0')
		return;

	mtx_lock(&dirlist_mtx);
	dle = devfs_dir_findent_locked(dir);
	KASSERT(dle != NULL, ("devfs_dir_unref: dir %s not referenced", dir));
	dle->refcnt--;
	KASSERT(dle->refcnt >= 0, ("devfs_dir_unref: negative refcnt"));
	if (dle->refcnt == 0) {
		LIST_REMOVE(dle, link);
		mtx_unlock(&dirlist_mtx);
		free(dle->dir, M_DEVFS4);
		free(dle, M_DEVFS4);
	} else
		mtx_unlock(&dirlist_mtx);
}