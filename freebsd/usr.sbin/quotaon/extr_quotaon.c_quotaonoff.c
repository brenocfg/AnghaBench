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
struct quotafile {int dummy; } ;
struct fstab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char** qfextension ; 
 int /*<<< orphan*/  quota_close (struct quotafile*) ; 
 char* quota_fsname (struct quotafile*) ; 
 scalar_t__ quota_off (struct quotafile*) ; 
 scalar_t__ quota_on (struct quotafile*) ; 
 struct quotafile* quota_open (struct fstab*,int,int /*<<< orphan*/ ) ; 
 char* quota_qfname (struct quotafile*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*,...) ; 

__attribute__((used)) static int
quotaonoff(struct fstab *fs, int offmode, int type)
{
	struct quotafile *qf;

	if ((qf = quota_open(fs, type, O_RDONLY)) == NULL)
		return (0);
	if (offmode) {
		if (quota_off(qf) != 0) {
			warn("%s", quota_fsname(qf));
			return (1);
		}
		if (vflag)
			printf("%s: quotas turned off\n", quota_fsname(qf));
		quota_close(qf);
		return(0);
	}
	if (quota_on(qf) != 0) {
		warn("using %s on %s", quota_qfname(qf), quota_fsname(qf));
		return (1);
	}
	if (vflag)
		printf("%s: %s quotas turned on with data file %s\n", 
		    quota_fsname(qf), qfextension[type], quota_qfname(qf));
	quota_close(qf);
	return(0);
}