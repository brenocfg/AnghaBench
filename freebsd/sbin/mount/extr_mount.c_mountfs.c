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
struct statfs {int dummy; } ;
struct cpa {int c; char** a; } ;
typedef  int /*<<< orphan*/  execname ;

/* Variables and functions */
 int MNT_FORCE ; 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  append_arg (struct cpa*,char*) ; 
 char* catopt (char*,char const*) ; 
 scalar_t__ checkpath (char const*,char*) ; 
 scalar_t__ debug ; 
 int exec_mountprog (char const*,char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstab_style ; 
 int /*<<< orphan*/  mangle (char*,struct cpa*) ; 
 int mount_fs (char const*,int,char**) ; 
 char* mountprog ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prmount (struct statfs*) ; 
 int /*<<< orphan*/  putfsent (struct statfs*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ statfs (char const*,struct statfs*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ use_mountprog (char const*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
mountfs(const char *vfstype, const char *spec, const char *name, int flags,
	const char *options, const char *mntopts)
{
	struct statfs sf;
	int i, ret;
	char *optbuf, execname[PATH_MAX], mntpath[PATH_MAX];
	static struct cpa mnt_argv;

	/* resolve the mountpoint with realpath(3) */
	if (checkpath(name, mntpath) != 0) {
		warn("%s", mntpath);
		return (1);
	}
	name = mntpath;

	if (mntopts == NULL)
		mntopts = "";
	optbuf = catopt(strdup(mntopts), options);

	if (strcmp(name, "/") == 0)
		flags |= MNT_UPDATE;
	if (flags & MNT_FORCE)
		optbuf = catopt(optbuf, "force");
	if (flags & MNT_RDONLY)
		optbuf = catopt(optbuf, "ro");
	/*
	 * XXX
	 * The mount_mfs (newfs) command uses -o to select the
	 * optimization mode.  We don't pass the default "-o rw"
	 * for that reason.
	 */
	if (flags & MNT_UPDATE)
		optbuf = catopt(optbuf, "update");

	/* Compatibility glue. */
	if (strcmp(vfstype, "msdos") == 0)
		vfstype = "msdosfs";

	/* Construct the name of the appropriate mount command */
	(void)snprintf(execname, sizeof(execname), "mount_%s", vfstype);

	mnt_argv.c = -1;
	append_arg(&mnt_argv, execname);
	mangle(optbuf, &mnt_argv);
	if (mountprog != NULL)
		strlcpy(execname, mountprog, sizeof(execname));

	append_arg(&mnt_argv, strdup(spec));
	append_arg(&mnt_argv, strdup(name));
	append_arg(&mnt_argv, NULL);

	if (debug) {
		if (use_mountprog(vfstype))
			printf("exec: %s", execname);
		else
			printf("mount -t %s", vfstype);
		for (i = 1; i < mnt_argv.c; i++)
			(void)printf(" %s", mnt_argv.a[i]);
		(void)printf("\n");
		free(optbuf);
		free(mountprog);
		mountprog = NULL;
		return (0);
	}

	if (use_mountprog(vfstype)) {
		ret = exec_mountprog(name, execname, mnt_argv.a);
	} else {
		ret = mount_fs(vfstype, mnt_argv.c, mnt_argv.a);
	}

	free(optbuf);
	free(mountprog);
	mountprog = NULL;

	if (verbose) {
		if (statfs(name, &sf) < 0) {
			warn("statfs %s", name);
			return (1);
		}
		if (fstab_style)
			putfsent(&sf);
		else
			prmount(&sf);
	}

	return (ret);
}