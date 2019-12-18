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
 size_t INT_MAX ; 
 scalar_t__ NI_MAXHOST ; 
 scalar_t__ a2port (char*) ; 
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hpdelim (char**) ; 
 char* opt_dequote (char const**,char const**) ; 
 char** recallocarray (char**,size_t,size_t,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
handle_permit(const char **optsp, int allow_bare_port,
    char ***permitsp, size_t *npermitsp, const char **errstrp)
{
	char *opt, *tmp, *cp, *host, **permits = *permitsp;
	size_t npermits = *npermitsp;
	const char *errstr = "unknown error";

	if (npermits > INT_MAX) {
		*errstrp = "too many permission directives";
		return -1;
	}
	if ((opt = opt_dequote(optsp, &errstr)) == NULL) {
		return -1;
	}
	if (allow_bare_port && strchr(opt, ':') == NULL) {
		/*
		 * Allow a bare port number in permitlisten to indicate a
		 * listen_host wildcard.
		 */
		if (asprintf(&tmp, "*:%s", opt) < 0) {
			*errstrp = "memory allocation failed";
			return -1;
		}
		free(opt);
		opt = tmp;
	}
	if ((tmp = strdup(opt)) == NULL) {
		free(opt);
		*errstrp = "memory allocation failed";
		return -1;
	}
	cp = tmp;
	/* validate syntax before recording it. */
	host = hpdelim(&cp);
	if (host == NULL || strlen(host) >= NI_MAXHOST) {
		free(tmp);
		free(opt);
		*errstrp = "invalid permission hostname";
		return -1;
	}
	/*
	 * don't want to use permitopen_port to avoid
	 * dependency on channels.[ch] here.
	 */
	if (cp == NULL ||
	    (strcmp(cp, "*") != 0 && a2port(cp) <= 0)) {
		free(tmp);
		free(opt);
		*errstrp = "invalid permission port";
		return -1;
	}
	/* XXX - add streamlocal support */
	free(tmp);
	/* Record it */
	if ((permits = recallocarray(permits, npermits, npermits + 1,
	    sizeof(*permits))) == NULL) {
		free(opt);
		/* NB. don't update *permitsp if alloc fails */
		*errstrp = "memory allocation failed";
		return -1;
	}
	permits[npermits++] = opt;
	*permitsp = permits;
	*npermitsp = npermits;
	return 0;
}