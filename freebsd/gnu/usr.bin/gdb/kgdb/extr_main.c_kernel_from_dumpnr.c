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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 char* crashdir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  kernel ; 
 int snprintf (char*,int,char*,char*,...) ; 
 int stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
kernel_from_dumpnr(int nr)
{
	char path[PATH_MAX];
	FILE *info;
	char *s;
	struct stat st;
	int l;

	/*
	 * If there's a kernel image right here in the crash directory, then
	 * use it.  The kernel image is either called kernel.<nr> or is in a
	 * subdirectory kernel.<nr> and called kernel.  The latter allows us
	 * to collect the modules in the same place.
	 */
	snprintf(path, sizeof(path), "%s/kernel.%d", crashdir, nr);
	if (stat(path, &st) == 0) {
		if (S_ISREG(st.st_mode)) {
			kernel = strdup(path);
			return;
		}
		if (S_ISDIR(st.st_mode)) {
			snprintf(path, sizeof(path), "%s/kernel.%d/kernel",
			    crashdir, nr);
			if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
				kernel = strdup(path);
				return;
			}
		}
	}

	/*
	 * No kernel image here.  Parse the dump header.  The kernel object
	 * directory can be found there and we probably have the kernel
	 * image still in it.  The object directory may also have a kernel
	 * with debugging info (called kernel.debug).  If we have a debug
	 * kernel, use it.
	 */
	snprintf(path, sizeof(path), "%s/info.%d", crashdir, nr);
	info = fopen(path, "r");
	if (info == NULL) {
		warn("%s", path);
		return;
	}
	while (fgets(path, sizeof(path), info) != NULL) {
		l = strlen(path);
		if (l > 0 && path[l - 1] == '\n')
			path[--l] = '\0';
		if (strncmp(path, "    ", 4) == 0) {
			s = strchr(path, ':');
			s = (s == NULL) ? path + 4 : s + 1;
			l = snprintf(path, sizeof(path), "%s/kernel.debug", s);
			if (stat(path, &st) == -1 || !S_ISREG(st.st_mode)) {
				path[l - 6] = '\0';
				if (stat(path, &st) == -1 ||
				    !S_ISREG(st.st_mode))
					break;
			}
			kernel = strdup(path);
			break;
		}
	}
	fclose(info);
}