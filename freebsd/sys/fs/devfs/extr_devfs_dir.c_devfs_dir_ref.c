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
struct dirlistent {int refcnt; struct dirlistent* dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dirlistent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVFS4 ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct dirlistent* devfs_dir_findent_locked (char const*) ; 
 int /*<<< orphan*/  devfs_dirlist ; 
 int /*<<< orphan*/  dirlist_mtx ; 
 int /*<<< orphan*/  free (struct dirlistent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct dirlistent* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct dirlistent* strdup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devfs_dir_ref(const char *dir)
{
	struct dirlistent *dle, *dle_new;

	if (*dir == '\0')
		return;

	dle_new = malloc(sizeof(*dle), M_DEVFS4, M_WAITOK);
	dle_new->dir = strdup(dir, M_DEVFS4);
	dle_new->refcnt = 1;

	mtx_lock(&dirlist_mtx);
	dle = devfs_dir_findent_locked(dir);
	if (dle != NULL) {
		dle->refcnt++;
		mtx_unlock(&dirlist_mtx);
		free(dle_new->dir, M_DEVFS4);
		free(dle_new, M_DEVFS4);
		return;
	}
	LIST_INSERT_HEAD(&devfs_dirlist, dle_new, link);
	mtx_unlock(&dirlist_mtx);
}