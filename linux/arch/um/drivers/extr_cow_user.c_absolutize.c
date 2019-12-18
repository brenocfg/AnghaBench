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
typedef  int /*<<< orphan*/  save_cwd ;

/* Variables and functions */
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  cow_printf (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int absolutize(char *to, int size, char *from)
{
	char save_cwd[256], *slash;
	int remaining;

	if (getcwd(save_cwd, sizeof(save_cwd)) == NULL) {
		cow_printf("absolutize : unable to get cwd - errno = %d\n",
			   errno);
		return -1;
	}
	slash = strrchr(from, '/');
	if (slash != NULL) {
		*slash = '\0';
		if (chdir(from)) {
			*slash = '/';
			cow_printf("absolutize : Can't cd to '%s' - "
				   "errno = %d\n", from, errno);
			return -1;
		}
		*slash = '/';
		if (getcwd(to, size) == NULL) {
			cow_printf("absolutize : unable to get cwd of '%s' - "
			       "errno = %d\n", from, errno);
			return -1;
		}
		remaining = size - strlen(to);
		if (strlen(slash) + 1 > remaining) {
			cow_printf("absolutize : unable to fit '%s' into %d "
			       "chars\n", from, size);
			return -1;
		}
		strcat(to, slash);
	}
	else {
		if (strlen(save_cwd) + 1 + strlen(from) + 1 > size) {
			cow_printf("absolutize : unable to fit '%s' into %d "
			       "chars\n", from, size);
			return -1;
		}
		strcpy(to, save_cwd);
		strcat(to, "/");
		strcat(to, from);
	}
	if (chdir(save_cwd)) {
		cow_printf("absolutize : Can't cd to '%s' - "
			   "errno = %d\n", save_cwd, errno);
		return -1;
	}
	return 0;
}