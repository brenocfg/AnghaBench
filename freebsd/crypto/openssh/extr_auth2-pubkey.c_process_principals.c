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
typedef  int u_int ;
struct sshkey_cert {int dummy; } ;
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  loc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ check_principals_line (struct ssh*,char*,struct sshkey_cert const*,char*,struct sshauthopt**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,scalar_t__) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
process_principals(struct ssh *ssh, FILE *f, const char *file,
    const struct sshkey_cert *cert, struct sshauthopt **authoptsp)
{
	char loc[256], *line = NULL, *cp, *ep;
	size_t linesize = 0;
	u_long linenum = 0;
	u_int found_principal = 0;

	if (authoptsp != NULL)
		*authoptsp = NULL;

	while (getline(&line, &linesize, f) != -1) {
		linenum++;
		/* Always consume entire input */
		if (found_principal)
			continue;

		/* Skip leading whitespace. */
		for (cp = line; *cp == ' ' || *cp == '\t'; cp++)
			;
		/* Skip blank and comment lines. */
		if ((ep = strchr(cp, '#')) != NULL)
			*ep = '\0';
		if (!*cp || *cp == '\n')
			continue;

		snprintf(loc, sizeof(loc), "%.200s:%lu", file, linenum);
		if (check_principals_line(ssh, cp, cert, loc, authoptsp) == 0)
			found_principal = 1;
	}
	free(line);
	return found_principal;
}