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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int u_char ;
struct TYPE_2__ {scalar_t__* val; } ;
struct statfs {char* f_mntfromname; char* f_mntonname; char* f_fstypename; int f_flags; scalar_t__ f_owner; scalar_t__ f_syncwrites; scalar_t__ f_asyncwrites; scalar_t__ f_syncreads; scalar_t__ f_asyncreads; TYPE_1__ f_fsid; } ;
struct passwd {char* pw_name; } ;
struct opt {int o_opt; char* o_name; } ;

/* Variables and functions */
 int MNT_USER ; 
 int MNT_VISFLAGMASK ; 
 struct passwd* getpwuid (scalar_t__) ; 
 struct opt* optnames ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

void
prmount(struct statfs *sfp)
{
	uint64_t flags;
	unsigned int i;
	struct opt *o;
	struct passwd *pw;

	(void)printf("%s on %s (%s", sfp->f_mntfromname, sfp->f_mntonname,
	    sfp->f_fstypename);

	flags = sfp->f_flags & MNT_VISFLAGMASK;
	for (o = optnames; flags != 0 && o->o_opt != 0; o++)
		if (flags & o->o_opt) {
			(void)printf(", %s", o->o_name);
			flags &= ~o->o_opt;
		}
	/*
	 * Inform when file system is mounted by an unprivileged user
	 * or privileged non-root user.
	 */
	if ((flags & MNT_USER) != 0 || sfp->f_owner != 0) {
		(void)printf(", mounted by ");
		if ((pw = getpwuid(sfp->f_owner)) != NULL)
			(void)printf("%s", pw->pw_name);
		else
			(void)printf("%d", sfp->f_owner);
	}
	if (verbose) {
		if (sfp->f_syncwrites != 0 || sfp->f_asyncwrites != 0)
			(void)printf(", writes: sync %ju async %ju",
			    (uintmax_t)sfp->f_syncwrites,
			    (uintmax_t)sfp->f_asyncwrites);
		if (sfp->f_syncreads != 0 || sfp->f_asyncreads != 0)
			(void)printf(", reads: sync %ju async %ju",
			    (uintmax_t)sfp->f_syncreads,
			    (uintmax_t)sfp->f_asyncreads);
		if (sfp->f_fsid.val[0] != 0 || sfp->f_fsid.val[1] != 0) {
			printf(", fsid ");
			for (i = 0; i < sizeof(sfp->f_fsid); i++)
				printf("%02x", ((u_char *)&sfp->f_fsid)[i]);
		}
	}
	(void)printf(")\n");
}