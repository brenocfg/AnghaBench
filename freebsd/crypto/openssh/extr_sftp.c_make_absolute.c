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
 char* path_append (char const*,char*) ; 

__attribute__((used)) static char *
make_absolute(char *p, const char *pwd)
{
	char *abs_str;

	/* Derelativise */
	if (p && p[0] != '/') {
		abs_str = path_append(pwd, p);
		free(p);
		return(abs_str);
	} else
		return(p);
}