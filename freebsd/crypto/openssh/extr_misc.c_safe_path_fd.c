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
struct stat {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int safe_path (char const*,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
safe_path_fd(int fd, const char *file, struct passwd *pw,
    char *err, size_t errlen)
{
	struct stat st;

	/* check the open file to avoid races */
	if (fstat(fd, &st) < 0) {
		snprintf(err, errlen, "cannot stat file %s: %s",
		    file, strerror(errno));
		return -1;
	}
	return safe_path(file, &st, pw->pw_dir, pw->pw_uid, err, errlen);
}