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
 int /*<<< orphan*/  ALL_MODE ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char const*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int
do_creat(const char *pfile)
{
	int fd, ret = 0;

	if (pfile == NULL) {
		return (-1);
	}

	if ((fd = creat(pfile, ALL_MODE)) == -1) {
		ret = errno;
	}
	if (fd != -1) {
		(void) close(fd);
	}

	if (ret != 0) {
		fprintf(stderr, "creat(%s, ALL_MODE)\n", pfile);
		exit(1);
	}

	return (ret);
}