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
typedef  int /*<<< orphan*/  uint8_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int /*<<< orphan*/  IFTODT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int dirfd (int /*<<< orphan*/ *) ; 
 int fstatat (int,char const*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static uint8_t
trail_type(DIR *dirfp, const char *filename)
{
	struct stat sb;
	int dfd;

	PJDLOG_ASSERT(dirfp != NULL);

	dfd = dirfd(dirfp);
	PJDLOG_ASSERT(dfd >= 0);
	if (fstatat(dfd, filename, &sb, AT_SYMLINK_NOFOLLOW) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to stat \"%s\"", filename);
		return (DT_UNKNOWN);
	}
	return (IFTODT(sb.st_mode));
}