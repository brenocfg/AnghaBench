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
 char* _PATH_DEFPATH ; 
 int execvPe (char const*,char const*,char* const*,char* const*) ; 
 char* getenv (char*) ; 

int
_execvpe(const char *name, char * const argv[], char * const envp[])
{
	const char *path;

	/* Get the path we're searching. */
	if ((path = getenv("PATH")) == NULL)
		path = _PATH_DEFPATH;

	return (execvPe(name, path, argv, envp));
}