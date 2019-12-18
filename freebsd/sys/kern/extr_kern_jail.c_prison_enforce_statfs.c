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
struct prison {scalar_t__ pr_enforce_statfs; int /*<<< orphan*/  pr_path; TYPE_1__* pr_root; } ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  jpath ;
struct TYPE_2__ {struct mount* v_mount; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ prison_canseemount (struct ucred*,struct mount*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

void
prison_enforce_statfs(struct ucred *cred, struct mount *mp, struct statfs *sp)
{
	char jpath[MAXPATHLEN];
	struct prison *pr;
	size_t len;

	pr = cred->cr_prison;
	if (pr->pr_enforce_statfs == 0)
		return;
	if (prison_canseemount(cred, mp) != 0) {
		bzero(sp->f_mntonname, sizeof(sp->f_mntonname));
		strlcpy(sp->f_mntonname, "[restricted]",
		    sizeof(sp->f_mntonname));
		return;
	}
	if (pr->pr_root->v_mount == mp) {
		/*
		 * Clear current buffer data, so we are sure nothing from
		 * the valid path left there.
		 */
		bzero(sp->f_mntonname, sizeof(sp->f_mntonname));
		*sp->f_mntonname = '/';
		return;
	}
	/*
	 * If jail's chroot directory is set to "/" we should be able to see
	 * all mount-points from inside a jail.
	 */
	if (strcmp(pr->pr_path, "/") == 0)
		return;
	len = strlen(pr->pr_path);
	strlcpy(jpath, sp->f_mntonname + len, sizeof(jpath));
	/*
	 * Clear current buffer data, so we are sure nothing from
	 * the valid path left there.
	 */
	bzero(sp->f_mntonname, sizeof(sp->f_mntonname));
	if (*jpath == '\0') {
		/* Should never happen. */
		*sp->f_mntonname = '/';
	} else {
		strlcpy(sp->f_mntonname, jpath, sizeof(sp->f_mntonname));
	}
}