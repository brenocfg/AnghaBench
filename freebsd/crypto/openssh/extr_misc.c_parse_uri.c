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
 char const* cleanhostname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hpdelim2 (char**,char*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char* urldecode (char*) ; 
 int /*<<< orphan*/  valid_domain (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xstrdup (char const*) ; 

int
parse_uri(const char *scheme, const char *uri, char **userp, char **hostp,
    int *portp, char **pathp)
{
	char *uridup, *cp, *tmp, ch;
	char *user = NULL, *host = NULL, *path = NULL;
	int port = -1, ret = -1;
	size_t len;

	len = strlen(scheme);
	if (strncmp(uri, scheme, len) != 0 || strncmp(uri + len, "://", 3) != 0)
		return 1;
	uri += len + 3;

	if (userp != NULL)
		*userp = NULL;
	if (hostp != NULL)
		*hostp = NULL;
	if (portp != NULL)
		*portp = -1;
	if (pathp != NULL)
		*pathp = NULL;

	uridup = tmp = xstrdup(uri);

	/* Extract optional ssh-info (username + connection params) */
	if ((cp = strchr(tmp, '@')) != NULL) {
		char *delim;

		*cp = '\0';
		/* Extract username and connection params */
		if ((delim = strchr(tmp, ';')) != NULL) {
			/* Just ignore connection params for now */
			*delim = '\0';
		}
		if (*tmp == '\0') {
			/* Empty username */
			goto out;
		}
		if ((user = urldecode(tmp)) == NULL)
			goto out;
		tmp = cp + 1;
	}

	/* Extract mandatory hostname */
	if ((cp = hpdelim2(&tmp, &ch)) == NULL || *cp == '\0')
		goto out;
	host = xstrdup(cleanhostname(cp));
	if (!valid_domain(host, 0, NULL))
		goto out;

	if (tmp != NULL && *tmp != '\0') {
		if (ch == ':') {
			/* Convert and verify port. */
			if ((cp = strchr(tmp, '/')) != NULL)
				*cp = '\0';
			if ((port = a2port(tmp)) <= 0)
				goto out;
			tmp = cp ? cp + 1 : NULL;
		}
		if (tmp != NULL && *tmp != '\0') {
			/* Extract optional path */
			if ((path = urldecode(tmp)) == NULL)
				goto out;
		}
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
	if (pathp != NULL) {
		*pathp = path;
		path = NULL;
	}
	ret = 0;
 out:
	free(uridup);
	free(user);
	free(host);
	free(path);
	return ret;
}