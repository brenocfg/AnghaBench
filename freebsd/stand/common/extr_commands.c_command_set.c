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
 int CMD_ERROR ; 
 int CMD_OK ; 
 int VE_UNVERIFIED_OK ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int putenv (char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 int ve_status_get (int) ; 

__attribute__((used)) static int
command_set(int argc, char *argv[])
{
	int	err;

	if (argc != 2) {
		command_errmsg = "wrong number of arguments";
		return (CMD_ERROR);
	} else {
#ifdef LOADER_VERIEXEC
		/*
		 * Impose restrictions if input is not verified
		 */
		const char *restricted[] = {
			"boot",
			"init",
			"loader.ve.",
			"rootfs",
			"secur",
			"vfs.",
			NULL,
		};
		const char **cp;
		int ves;

		ves = ve_status_get(-1);
		if (ves == VE_UNVERIFIED_OK) {
#ifdef LOADER_VERIEXEC_TESTING
			printf("Checking: %s\n", argv[1]);
#endif
			for (cp = restricted; *cp; cp++) {
				if (strncmp(argv[1], *cp, strlen(*cp)) == 0) {
					printf("Ignoring restricted variable: %s\n",
					    argv[1]);
					return (CMD_OK);
				}
			}
		}
#endif
		if ((err = putenv(argv[1])) != 0) {
			command_errmsg = strerror(err);
			return (CMD_ERROR);
		}
	}
	return (CMD_OK);
}