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
typedef  scalar_t__ u_long ;
struct sshkey {int dummy; } ;
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  loc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ check_authkey_line (struct ssh*,struct passwd*,struct sshkey*,char*,char*,struct sshauthopt**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_space (char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,scalar_t__) ; 

__attribute__((used)) static int
check_authkeys_file(struct ssh *ssh, struct passwd *pw, FILE *f,
    char *file, struct sshkey *key, struct sshauthopt **authoptsp)
{
	char *cp, *line = NULL, loc[256];
	size_t linesize = 0;
	int found_key = 0;
	u_long linenum = 0;

	if (authoptsp != NULL)
		*authoptsp = NULL;

	while (getline(&line, &linesize, f) != -1) {
		linenum++;
		/* Always consume entire file */
		if (found_key)
			continue;

		/* Skip leading whitespace, empty and comment lines. */
		cp = line;
		skip_space(&cp);
		if (!*cp || *cp == '\n' || *cp == '#')
			continue;
		snprintf(loc, sizeof(loc), "%.200s:%lu", file, linenum);
		if (check_authkey_line(ssh, pw, key, cp, loc, authoptsp) == 0)
			found_key = 1;
	}
	free(line);
	return found_key;
}