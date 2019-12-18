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
typedef  int /*<<< orphan*/  fn ;

/* Variables and functions */
 int LINKER_HINTS_VERSION ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hints ; 
 void* hints_end ; 
 char* linker_hints ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/ * read_hints (char*,size_t*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
read_linker_hints(void)
{
	char fn[MAXPATHLEN];
	char *modpath, *p, *q;
	size_t buflen, len;

	if (linker_hints == NULL) {
		if (sysctlbyname("kern.module_path", NULL, &buflen, NULL, 0) < 0)
			errx(1, "Can't find kernel module path.");
		modpath = malloc(buflen);
		if (modpath == NULL)
			err(1, "Can't get memory for modpath.");
		if (sysctlbyname("kern.module_path", modpath, &buflen, NULL, 0) < 0)
			errx(1, "Can't find kernel module path.");
		p = modpath;
		while ((q = strsep(&p, ";")) != NULL) {
			snprintf(fn, sizeof(fn), "%s/linker.hints", q);
			hints = read_hints(fn, &len);
			if (hints == NULL)
				continue;
			break;
		}
		if (q == NULL)
			errx(1, "Can't read linker hints file.");
	} else {
		hints = read_hints(linker_hints, &len);
		if (hints == NULL)
			err(1, "Can't open %s for reading", fn);
	}

	if (*(int *)(intptr_t)hints != LINKER_HINTS_VERSION) {
		warnx("Linker hints version %d doesn't match expected %d.",
		    *(int *)(intptr_t)hints, LINKER_HINTS_VERSION);
		free(hints);
		hints = NULL;
	}
	if (hints != NULL)
		hints_end = (void *)((intptr_t)hints + (intptr_t)len);
}