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

__attribute__((used)) static void
trim(char *buf, size_t len, const char *name)
{
	char *path = buf, *epath = buf + len;
	while (path < epath && (*path++ = *name++) != '\0')
		continue;
	path--;
	while (path > buf && *--path == '/')
		*path = '\0';
}