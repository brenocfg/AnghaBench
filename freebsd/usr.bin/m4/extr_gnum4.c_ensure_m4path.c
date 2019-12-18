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
 int TRUE ; 
 int /*<<< orphan*/  addtoincludepath (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* strsep (char**,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
ensure_m4path(void)
{
	static int envpathdone = 0;
	char *envpath;
	char *sweep;
	char *path;

	if (envpathdone)
		return;
	envpathdone = TRUE;
	envpath = getenv("M4PATH");
	if (!envpath)
		return;
	/* for portability: getenv result is read-only */
	envpath = xstrdup(envpath);
	for (sweep = envpath;
	    (path = strsep(&sweep, ":")) != NULL;)
	    addtoincludepath(path);
	free(envpath);
}