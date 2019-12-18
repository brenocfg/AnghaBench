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
typedef  size_t u_int ;
struct sshkey_cert {size_t nprincipals; int /*<<< orphan*/ * principals; } ;
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_debug_add (char*,char const*,char const*) ; 
 int /*<<< orphan*/  debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  debug3 (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshauthopt_free (struct sshauthopt*) ; 
 struct sshauthopt* sshauthopt_parse (char*,char const**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
check_principals_line(struct ssh *ssh, char *cp, const struct sshkey_cert *cert,
    const char *loc, struct sshauthopt **authoptsp)
{
	u_int i, found = 0;
	char *ep, *line_opts;
	const char *reason = NULL;
	struct sshauthopt *opts = NULL;

	if (authoptsp != NULL)
		*authoptsp = NULL;

	/* Trim trailing whitespace. */
	ep = cp + strlen(cp) - 1;
	while (ep > cp && (*ep == '\n' || *ep == ' ' || *ep == '\t'))
		*ep-- = '\0';

	/*
	 * If the line has internal whitespace then assume it has
	 * key options.
	 */
	line_opts = NULL;
	if ((ep = strrchr(cp, ' ')) != NULL ||
	    (ep = strrchr(cp, '\t')) != NULL) {
		for (; *ep == ' ' || *ep == '\t'; ep++)
			;
		line_opts = cp;
		cp = ep;
	}
	if ((opts = sshauthopt_parse(line_opts, &reason)) == NULL) {
		debug("%s: bad principals options: %s", loc, reason);
		auth_debug_add("%s: bad principals options: %s", loc, reason);
		return -1;
	}
	/* Check principals in cert against those on line */
	for (i = 0; i < cert->nprincipals; i++) {
		if (strcmp(cp, cert->principals[i]) != 0)
			continue;
		debug3("%s: matched principal \"%.100s\"",
		    loc, cert->principals[i]);
		found = 1;
	}
	if (found && authoptsp != NULL) {
		*authoptsp = opts;
		opts = NULL;
	}
	sshauthopt_free(opts);
	return found ? 0 : -1;
}