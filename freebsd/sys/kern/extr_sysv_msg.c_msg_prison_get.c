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
struct prison {int dummy; } ;
typedef  int /*<<< orphan*/  jsys ;

/* Variables and functions */
 int ENOENT ; 
 int JAIL_SYS_DISABLE ; 
 int JAIL_SYS_INHERIT ; 
 int JAIL_SYS_NEW ; 
 int /*<<< orphan*/  msg_prison_slot ; 
 struct prison* osd_jail_get (struct prison*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prison_lock (struct prison*) ; 
 int /*<<< orphan*/  prison_unlock (struct prison*) ; 
 int vfs_setopt (struct vfsoptlist*,char*,int*,int) ; 

__attribute__((used)) static int
msg_prison_get(void *obj, void *data)
{
	struct prison *pr = obj;
	struct prison *rpr;
	struct vfsoptlist *opts = data;
	int error, jsys;

	/* Set sysvmsg based on the jail's root prison. */
	prison_lock(pr);
	rpr = osd_jail_get(pr, msg_prison_slot);
	prison_unlock(pr);
	jsys = rpr == NULL ? JAIL_SYS_DISABLE
	    : rpr == pr ? JAIL_SYS_NEW : JAIL_SYS_INHERIT;
	error = vfs_setopt(opts, "sysvmsg", &jsys, sizeof(jsys));
	if (error == ENOENT)
		error = 0;
	return (error);
}