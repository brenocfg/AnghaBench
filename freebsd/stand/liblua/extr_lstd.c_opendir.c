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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

DIR *
opendir(const char *name)
{
	DIR *dp;
	int fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return NULL;
	dp = fdopendir(fd);
	if (dp == NULL)
		close(fd);
	return dp;
}