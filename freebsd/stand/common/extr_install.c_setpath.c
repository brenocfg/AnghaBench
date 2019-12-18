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
 int ENOMEM ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
setpath(char **what, char *val)
{
	char *path;
	size_t len;
	int rel;

	len = strlen(val) + 1;
	rel = (val[0] != '/') ? 1 : 0;
	path = malloc(len + rel);
	if (path == NULL)
		return (ENOMEM);
	path[0] = '/';
	strcpy(path + rel, val);

	*what = path;
	return (0);
}