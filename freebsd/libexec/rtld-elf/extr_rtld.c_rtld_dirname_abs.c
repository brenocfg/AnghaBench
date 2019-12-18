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
 int /*<<< orphan*/  dbg (char*,char const*,char*) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
rtld_dirname_abs(const char *path, char *base)
{
	char *last;

	if (realpath(path, base) == NULL)
		return (-1);
	dbg("%s -> %s", path, base);
	last = strrchr(base, '/');
	if (last == NULL)
		return (-1);
	if (last != base)
		*last = '\0';
	return (0);
}