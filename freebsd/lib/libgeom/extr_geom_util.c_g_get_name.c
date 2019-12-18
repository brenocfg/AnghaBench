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
 int /*<<< orphan*/  g_close (int) ; 
 int g_open_by_ident (char const*,int /*<<< orphan*/ ,char*,size_t) ; 

int
g_get_name(const char *ident, char *name, size_t size)
{
	int fd;

	fd = g_open_by_ident(ident, 0, name, size);
	if (fd == -1)
		return (-1);
	g_close(fd);
	return (0);
}