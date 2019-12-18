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
 int a2port (char*) ; 
 int /*<<< orphan*/  cleanhostname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hpdelim (char**) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

int
parse_user_host_port(const char *s, char **userp, char **hostp, int *portp)
{
	char *sdup, *cp, *tmp;
	char *user = NULL, *host = NULL;
	int port = -1, ret = -1;

	if (userp != NULL)
		*userp = NULL;
	if (hostp != NULL)
		*hostp = NULL;
	if (portp != NULL)
		*portp = -1;

	if ((sdup = tmp = strdup(s)) == NULL)
		return -1;
	/* Extract optional username */
	if ((cp = strrchr(tmp, '@')) != NULL) {
		*cp = '\0';
		if (*tmp == '\0')
			goto out;
		if ((user = strdup(tmp)) == NULL)
			goto out;
		tmp = cp + 1;
	}
	/* Extract mandatory hostname */
	if ((cp = hpdelim(&tmp)) == NULL || *cp == '\0')
		goto out;
	host = xstrdup(cleanhostname(cp));
	/* Convert and verify optional port */
	if (tmp != NULL && *tmp != '\0') {
		if ((port = a2port(tmp)) <= 0)
			goto out;
	}
	/* Success */
	if (userp != NULL) {
		*userp = user;
		user = NULL;
	}
	if (hostp != NULL) {
		*hostp = host;
		host = NULL;
	}
	if (portp != NULL)
		*portp = port;
	ret = 0;
 out:
	free(sdup);
	free(user);
	free(host);
	return ret;
}