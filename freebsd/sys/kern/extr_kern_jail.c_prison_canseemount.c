#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {struct prison* cr_prison; } ;
struct statfs {char* f_mntonname; } ;
struct prison {int pr_enforce_statfs; int /*<<< orphan*/  pr_path; TYPE_1__* pr_root; } ;
struct mount {struct statfs mnt_stat; } ;
struct TYPE_2__ {struct mount* v_mount; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,size_t) ; 

int
prison_canseemount(struct ucred *cred, struct mount *mp)
{
	struct prison *pr;
	struct statfs *sp;
	size_t len;

	pr = cred->cr_prison;
	if (pr->pr_enforce_statfs == 0)
		return (0);
	if (pr->pr_root->v_mount == mp)
		return (0);
	if (pr->pr_enforce_statfs == 2)
		return (ENOENT);
	/*
	 * If jail's chroot directory is set to "/" we should be able to see
	 * all mount-points from inside a jail.
	 * This is ugly check, but this is the only situation when jail's
	 * directory ends with '/'.
	 */
	if (strcmp(pr->pr_path, "/") == 0)
		return (0);
	len = strlen(pr->pr_path);
	sp = &mp->mnt_stat;
	if (strncmp(pr->pr_path, sp->f_mntonname, len) != 0)
		return (ENOENT);
	/*
	 * Be sure that we don't have situation where jail's root directory
	 * is "/some/path" and mount point is "/some/pathpath".
	 */
	if (sp->f_mntonname[len] != '\0' && sp->f_mntonname[len] != '/')
		return (ENOENT);
	return (0);
}