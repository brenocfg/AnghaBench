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
 char* CPP ; 
 char* CPPFLAGS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  insarg (int,char*) ; 
 char* strsep (char**,char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
prepend_cpp(void)
{
	int idx = 1;
	const char *var;
	char *dupvar, *s, *t;

	if (CPP != NULL)
		insarg(0, CPP);
	else if ((var = getenv("RPCGEN_CPP")) == NULL)
		insarg(0, "/usr/bin/cpp");
	else {
		/* Parse command line in a rudimentary way */
		dupvar = xstrdup(var);
		for (s = dupvar, idx = 0; (t = strsep(&s, " \t")) != NULL; ) {
			if (t[0])
				insarg(idx++, t);
		}
		free(dupvar);
	}

	insarg(idx, CPPFLAGS);
}