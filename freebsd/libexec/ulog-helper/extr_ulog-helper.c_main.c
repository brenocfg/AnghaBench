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
 int EX_OK ; 
 int EX_OSERR ; 
 int EX_USAGE ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 char* get_username () ; 
 char* ptsname (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  ulog_login (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  ulog_logout (char const*) ; 

int
main(int argc, char *argv[])
{
	const char *line, *user, *host;

	/* Device line name. */
	if ((line = ptsname(STDIN_FILENO)) == NULL)
		return (EX_USAGE);

	if ((argc == 2 || argc == 3) && strcmp(argv[1], "login") == 0) {
		/* Username. */
		user = get_username();
		if (user == NULL)
			return (EX_OSERR);

		/* Hostname. */
		host = argc == 3 ? argv[2] : NULL;

		ulog_login(line, user, host);
		return (EX_OK);
	} else if (argc == 2 && strcmp(argv[1], "logout") == 0) {
		ulog_logout(line);
		return (EX_OK);
	}

	return (EX_USAGE);
}