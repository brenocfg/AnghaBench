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
 int AF_INET6 ; 
 int evutil_inet_pton (int,char const*,void*) ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned int if_nametoindex (char*) ; 
 char* mm_strdup (char const*) ; 
 char* strchr (char const*,char) ; 
 unsigned int strtoul (char*,char**,int) ; 

int
evutil_inet_pton_scope(int af, const char *src, void *dst, unsigned *indexp)
{
	int r;
	unsigned if_index;
	char *check, *cp, *tmp_src;

	*indexp = 0; /* Reasonable default */

	/* Bail out if not IPv6 */
	if (af != AF_INET6)
		return evutil_inet_pton(af, src, dst);

	cp = strchr(src, '%');

	/* Bail out if no zone ID */
	if (cp == NULL)
		return evutil_inet_pton(af, src, dst);

	if_index = if_nametoindex(cp + 1);
	if (if_index == 0) {
		/* Could be numeric */
		if_index = strtoul(cp + 1, &check, 10);
		if (check[0] != '\0')
			return 0;
	}
	*indexp = if_index;
	tmp_src = mm_strdup(src);
	cp = strchr(tmp_src, '%');
	*cp = '\0';
	r = evutil_inet_pton(af, tmp_src, dst);
	free(tmp_src);
	return r;
}