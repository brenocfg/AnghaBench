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
struct timespec {int dummy; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; struct timespec st_mtim; struct timespec st_atim; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 scalar_t__ EOPNOTSUPP ; 
 scalar_t__ EPERM ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISGID ; 
 int S_ISUID ; 
 scalar_t__ chflags (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char const*,int) ; 
 scalar_t__ chown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cwarn (char*,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ utimensat (int /*<<< orphan*/ ,char const*,struct timespec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setfile(const char *name, struct stat *fs)
{
	static struct timespec tspec[2];

	fs->st_mode &= S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO;

	tspec[0] = fs->st_atim;
	tspec[1] = fs->st_mtim;
	if (utimensat(AT_FDCWD, name, tspec, 0))
		cwarn("utimensat: %s", name);

	/*
	 * Changing the ownership probably won't succeed, unless we're root
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid/gid before setting
	 * the mode; current BSD behavior is to remove all setuid bits on
	 * chown.  If chown fails, lose setuid/setgid bits.
	 */
	if (chown(name, fs->st_uid, fs->st_gid)) {
		if (errno != EPERM)
			cwarn("chown: %s", name);
		fs->st_mode &= ~(S_ISUID|S_ISGID);
	}
	if (chmod(name, fs->st_mode) && errno != EOPNOTSUPP)
		cwarn("chmod: %s", name);

	if (chflags(name, fs->st_flags) && errno != EOPNOTSUPP)
		cwarn("chflags: %s", name);
}