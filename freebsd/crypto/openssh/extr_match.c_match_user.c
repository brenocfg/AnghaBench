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
 int /*<<< orphan*/  free (char*) ; 
 int match_host_and_ip (char const*,char const*,char*) ; 
 int match_pattern (char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

int
match_user(const char *user, const char *host, const char *ipaddr,
    const char *pattern)
{
	char *p, *pat;
	int ret;

	/* test mode */
	if (user == NULL && host == NULL && ipaddr == NULL) {
		if ((p = strchr(pattern, '@')) != NULL &&
		    match_host_and_ip(NULL, NULL, p + 1) < 0)
			return -1;
		return 0;
	}

	if ((p = strchr(pattern,'@')) == NULL)
		return match_pattern(user, pattern);

	pat = xstrdup(pattern);
	p = strchr(pat, '@');
	*p++ = '\0';

	if ((ret = match_pattern(user, pat)) == 1)
		ret = match_host_and_ip(host, ipaddr, p);
	free(pat);

	return ret;
}