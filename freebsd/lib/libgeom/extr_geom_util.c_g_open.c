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
 int /*<<< orphan*/  free (char*) ; 
 char* g_device_path_open (char const*,int*,int) ; 

int
g_open(const char *name, int dowrite)
{
	char *path;
	int fd;

	path = g_device_path_open(name, &fd, dowrite);
	if (path != NULL)
		free(path);
	return (fd);
}