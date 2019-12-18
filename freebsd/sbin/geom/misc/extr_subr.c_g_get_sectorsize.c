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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_close (int) ; 
 int g_open (char const*,int /*<<< orphan*/ ) ; 
 int g_sectorsize (int) ; 

unsigned int
g_get_sectorsize(const char *name)
{
	ssize_t sectorsize;
	int fd;

	fd = g_open(name, 0);
	if (fd == -1)
		return (0);
	sectorsize = g_sectorsize(fd);
	if (sectorsize == -1)
		sectorsize = 0;
	(void)g_close(fd);
	return ((unsigned int)sectorsize);
}