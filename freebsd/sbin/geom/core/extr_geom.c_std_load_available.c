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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  paths ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 char* class_name ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
std_load_available(void)
{
	char name[MAXPATHLEN], paths[MAXPATHLEN * 8], *p;
	struct stat sb;
	size_t len;

	snprintf(name, sizeof(name), "g_%s", class_name);
	/*
	 * If already in kernel, "load" command is not available.
	 */
	if (modfind(name) >= 0)
		return (0);
	bzero(paths, sizeof(paths));
	len = sizeof(paths);
	if (sysctlbyname("kern.module_path", paths, &len, NULL, 0) < 0)
		err(EXIT_FAILURE, "sysctl(kern.module_path)");
	for (p = strtok(paths, ";"); p != NULL; p = strtok(NULL, ";")) {
		snprintf(name, sizeof(name), "%s/geom_%s.ko", p, class_name);
		/*
		 * If geom_<name>.ko file exists, "load" command is available.
		 */
		if (stat(name, &sb) == 0)
			return (1);
	}
	return (0);
}