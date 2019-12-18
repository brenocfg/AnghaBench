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
struct statfs {int /*<<< orphan*/  f_mntfromname; } ;
struct stat {int st_flags; int st_size; int /*<<< orphan*/  st_mode; } ;
struct mkuz_cfg {int fdr; int /*<<< orphan*/  iname; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int SF_SNAPSHOT ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ fstatfs (int,struct statfs*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

off_t
mkuz_get_insize(struct mkuz_cfg *cfp)
{
	int ffd;
	off_t ms;
	struct stat sb;
	struct statfs statfsbuf;

	if (fstat(cfp->fdr, &sb) != 0) {
		warn("fstat(%s)", cfp->iname);
		return (-1);
	}
	if ((sb.st_flags & SF_SNAPSHOT) != 0) {
		if (fstatfs(cfp->fdr, &statfsbuf) != 0) {
			warn("fstatfs(%s)", cfp->iname);
			return (-1);
		}
		ffd = open(statfsbuf.f_mntfromname, O_RDONLY);
		if (ffd < 0) {
			warn("open(%s, O_RDONLY)", statfsbuf.f_mntfromname);
			return (-1);
		}
		if (ioctl(ffd, DIOCGMEDIASIZE, &ms) < 0) {
			warn("ioctl(DIOCGMEDIASIZE)");
			close(ffd);
			return (-1);
		}
		close(ffd);
		sb.st_size = ms;
	} else if (S_ISCHR(sb.st_mode)) {
		if (ioctl(cfp->fdr, DIOCGMEDIASIZE, &ms) < 0) {
			warn("ioctl(DIOCGMEDIASIZE)");
			return (-1);
		}
		sb.st_size = ms;
	} else if (!S_ISREG(sb.st_mode)) {
		warnx("%s: not a character device or regular file\n",
			cfp->iname);
		return (-1);
	}
	return (sb.st_size);
}