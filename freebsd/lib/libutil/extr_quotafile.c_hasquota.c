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
typedef  int /*<<< orphan*/  usrname ;
struct statfs {char* f_mntonname; } ;
struct fstab {char* fs_file; int /*<<< orphan*/  fs_mntops; } ;
typedef  int /*<<< orphan*/  grpname ;

/* Variables and functions */
 int BUFSIZ ; 
 size_t GRPQUOTA ; 
 char* QUOTAFILENAME ; 
 size_t USRQUOTA ; 
 char** qfextension ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
hasquota(struct fstab *fs, int type, char *qfnamep, int qfbufsize)
{
	char *opt;
	char *cp;
	struct statfs sfb;
	char buf[BUFSIZ];
	static char initname, usrname[100], grpname[100];

	/*
	 * 1) we only need one of these
	 * 2) fstab may specify a different filename
	 */
	if (!initname) {
		(void)snprintf(usrname, sizeof(usrname), "%s%s",
		    qfextension[USRQUOTA], QUOTAFILENAME);
		(void)snprintf(grpname, sizeof(grpname), "%s%s",
		    qfextension[GRPQUOTA], QUOTAFILENAME);
		initname = 1;
	}
	strcpy(buf, fs->fs_mntops);
	for (opt = strtok(buf, ","); opt; opt = strtok(NULL, ",")) {
		if ((cp = strchr(opt, '=')))
			*cp++ = '\0';
		if (type == USRQUOTA && strcmp(opt, usrname) == 0)
			break;
		if (type == GRPQUOTA && strcmp(opt, grpname) == 0)
			break;
	}
	if (!opt)
		return (0);
	/*
	 * Ensure that the filesystem is mounted.
	 */
	if (statfs(fs->fs_file, &sfb) != 0 ||
	    strcmp(fs->fs_file, sfb.f_mntonname)) {
		return (0);
	}
	if (cp) {
		strlcpy(qfnamep, cp, qfbufsize);
	} else {
		(void)snprintf(qfnamep, qfbufsize, "%s/%s.%s", fs->fs_file,
		    QUOTAFILENAME, qfextension[type]);
	}
	return (1);
}