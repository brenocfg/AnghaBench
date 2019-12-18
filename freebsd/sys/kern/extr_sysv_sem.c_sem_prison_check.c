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
struct vfsoptlist {int dummy; } ;
struct prison {int /*<<< orphan*/  pr_parent; } ;
typedef  int /*<<< orphan*/  jsys ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
#define  JAIL_SYS_DISABLE 130 
#define  JAIL_SYS_INHERIT 129 
#define  JAIL_SYS_NEW 128 
 struct prison* osd_jail_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prison_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prison_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_prison_slot ; 
 int vfs_copyopt (struct vfsoptlist*,char*,int*,int) ; 

__attribute__((used)) static int
sem_prison_check(void *obj, void *data)
{
	struct prison *pr = obj;
	struct prison *prpr;
	struct vfsoptlist *opts = data;
	int error, jsys;

	/*
	 * sysvsem is a jailsys integer.
	 * It must be "disable" if the parent jail is disabled.
	 */
	error = vfs_copyopt(opts, "sysvsem", &jsys, sizeof(jsys));
	if (error != ENOENT) {
		if (error != 0)
			return (error);
		switch (jsys) {
		case JAIL_SYS_DISABLE:
			break;
		case JAIL_SYS_NEW:
		case JAIL_SYS_INHERIT:
			prison_lock(pr->pr_parent);
			prpr = osd_jail_get(pr->pr_parent, sem_prison_slot);
			prison_unlock(pr->pr_parent);
			if (prpr == NULL)
				return (EPERM);
			break;
		default:
			return (EINVAL);
		}
	}

	return (0);
}