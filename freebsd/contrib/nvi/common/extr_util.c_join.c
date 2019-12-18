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
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

char *
join(
	char *path1,
	char *path2)
{
	char *p;

	if (path1[0] == '\0' || path2[0] == '/')
		return strdup(path2);
	(void)asprintf(&p, path1[strlen(path1)-1] == '/' ?
	    "%s%s" : "%s/%s", path1, path2);
	return p;
}