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
 char* ARGEXT ; 
 char* locase (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

char *
make_argname(const char *pname, const char *vname)
{
	char *name;

	name = xmalloc(strlen(pname) + strlen(vname) + strlen(ARGEXT) + 3);
	sprintf(name, "%s_%s_%s", locase(pname), vname, ARGEXT);
	return (name);
}