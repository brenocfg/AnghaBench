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
 int SSH_TUNID_ANY ; 
 int SSH_TUNID_ERR ; 
 int /*<<< orphan*/  SSH_TUNID_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 char* strchr (char*,char) ; 
 int strtonum (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char* xstrdup (char const*) ; 

int
a2tun(const char *s, int *remote)
{
	const char *errstr = NULL;
	char *sp, *ep;
	int tun;

	if (remote != NULL) {
		*remote = SSH_TUNID_ANY;
		sp = xstrdup(s);
		if ((ep = strchr(sp, ':')) == NULL) {
			free(sp);
			return (a2tun(s, NULL));
		}
		ep[0] = '\0'; ep++;
		*remote = a2tun(ep, NULL);
		tun = a2tun(sp, NULL);
		free(sp);
		return (*remote == SSH_TUNID_ERR ? *remote : tun);
	}

	if (strcasecmp(s, "any") == 0)
		return (SSH_TUNID_ANY);

	tun = strtonum(s, 0, SSH_TUNID_MAX, &errstr);
	if (errstr != NULL)
		return (SSH_TUNID_ERR);

	return (tun);
}