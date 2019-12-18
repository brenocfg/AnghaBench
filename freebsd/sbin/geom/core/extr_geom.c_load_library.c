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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ G_LIB_VERSION ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * class_commands ; 
 char* class_name ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 int /*<<< orphan*/  dlerror () ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/  library_path () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/ * version ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load_library(void)
{
	char *curpath, path[MAXPATHLEN], *tofree, *totalpath;
	uint32_t *lib_version;
	void *dlh;
	int ret;

	ret = 0;
	tofree = totalpath = strdup(library_path());
	if (totalpath == NULL)
		err(EXIT_FAILURE, "Not enough memory for library path");

	if (strchr(totalpath, ':') != NULL)
		curpath = strsep(&totalpath, ":");
	else
		curpath = totalpath;
	/* Traverse the paths to find one that contains the library we want. */
	while (curpath != NULL) {
		snprintf(path, sizeof(path), "%s/geom_%s.so", curpath,
		    class_name);
		ret = access(path, F_OK);
		if (ret == -1) {
			if (errno == ENOENT) {
				/*
				 * If we cannot find library, try the next
				 * path.
				 */
				curpath = strsep(&totalpath, ":");
				continue;
			}
			err(EXIT_FAILURE, "Cannot access library");
		}
		break;
	}
	free(tofree);
	/* No library was found, but standard commands can still be used */
	if (ret == -1)
		return;
	dlh = dlopen(path, RTLD_NOW);
	if (dlh == NULL)
		errx(EXIT_FAILURE, "Cannot open library: %s.", dlerror());
	lib_version = dlsym(dlh, "lib_version");
	if (lib_version == NULL) {
		warnx("Cannot find symbol %s: %s.", "lib_version", dlerror());
		dlclose(dlh);
		exit(EXIT_FAILURE);
	}
	if (*lib_version != G_LIB_VERSION) {
		dlclose(dlh);
		errx(EXIT_FAILURE, "%s and %s are not synchronized.",
		    getprogname(), path);
	}
	version = dlsym(dlh, "version");
	if (version == NULL) {
		warnx("Cannot find symbol %s: %s.", "version", dlerror());
		dlclose(dlh);
		exit(EXIT_FAILURE);
	}
	class_commands = dlsym(dlh, "class_commands");
	if (class_commands == NULL) {
		warnx("Cannot find symbol %s: %s.", "class_commands",
		    dlerror());
		dlclose(dlh);
		exit(EXIT_FAILURE);
	}
}