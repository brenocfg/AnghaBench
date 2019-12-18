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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,struct in6_addr*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static void
nptv6_parse_prefix(const char *arg, struct in6_addr *prefix, int *len)
{
	char *p, *l;

	p = strdup(arg);
	if (p == NULL)
		err(EX_OSERR, NULL);
	if ((l = strchr(p, '/')) != NULL)
		*l++ = '\0';
	if (inet_pton(AF_INET6, p, prefix) != 1)
		errx(EX_USAGE, "Bad prefix: %s", p);
	if (l != NULL) {
		*len = (int)strtol(l, &l, 10);
		if (*l != '\0' || *len <= 0 || *len > 64)
			errx(EX_USAGE, "Bad prefix length: %s", arg);
	} else
		*len = 0;
	free(p);
}