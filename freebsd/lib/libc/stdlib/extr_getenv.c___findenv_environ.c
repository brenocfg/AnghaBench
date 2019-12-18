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
 char** environ ; 
 scalar_t__ strncmpeq (char*,char const*,size_t) ; 

__attribute__((used)) static char *
__findenv_environ(const char *name, size_t nameLen)
{
	int envNdx;

	/* Find variable within environ. */
	for (envNdx = 0; environ[envNdx] != NULL; envNdx++)
		if (strncmpeq(environ[envNdx], name, nameLen))
			return (&(environ[envNdx][nameLen + sizeof("=") - 1]));

	return (NULL);
}