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

/* Variables and functions */
 int chown (char const*,scalar_t__,scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  stderr ; 

int
do_chown(const char *pfile)
{
	int ret = 0;

	if (pfile == NULL) {
		return (-1);
	}

	if (chown(pfile, getuid(), getgid()) == -1) {
		ret = errno;
	}
	if (ret != 0) {
		fprintf(stderr, "chown(%s, %d, %d)\n", pfile, (int)getuid(),
		    (int)getgid());
		exit(1);
	}

	return (ret);
}