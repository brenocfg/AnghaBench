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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* remote ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void
verify_remote(void)
{
	char path[PATH_MAX];
	struct stat st;

	if (stat(remote, &st) != 0) {
		snprintf(path, sizeof(path), "/dev/%s", remote);
		if (stat(path, &st) != 0)
			return;
		free(remote);
		remote = strdup(path);
	}
	if (!S_ISCHR(st.st_mode) && !S_ISFIFO(st.st_mode))
		errx(1, "%s: not a special file, FIFO or socket", remote);
}