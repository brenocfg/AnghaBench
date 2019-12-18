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
 int /*<<< orphan*/  DIOCGPROVIDERNAME ; 
 int MAXPATHLEN ; 
 int g_ioctl_arg (int,int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 

char *
g_providername(int fd)
{
	char name[MAXPATHLEN];

	if (g_ioctl_arg(fd, DIOCGPROVIDERNAME, name) == -1)
		return (NULL);
	return (strdup(name));
}