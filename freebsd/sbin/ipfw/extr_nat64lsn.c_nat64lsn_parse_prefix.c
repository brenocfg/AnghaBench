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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int inet_pton (int,char*,void*) ; 
 int /*<<< orphan*/  nat64lsn_apply_mask (int,void*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static void
nat64lsn_parse_prefix(const char *arg, int af, void *prefix, uint16_t *plen)
{
	char *p, *l;

	p = strdup(arg);
	if (p == NULL)
		err(EX_OSERR, NULL);
	if ((l = strchr(p, '/')) != NULL)
		*l++ = '\0';
	if (l == NULL)
		errx(EX_USAGE, "Prefix length required");
	if (inet_pton(af, p, prefix) != 1)
		errx(EX_USAGE, "Bad prefix: %s", p);
	*plen = (uint16_t)strtol(l, &l, 10);
	if (*l != '\0' || *plen == 0 || (af == AF_INET && *plen > 32) ||
	    (af == AF_INET6 && *plen > 96))
		errx(EX_USAGE, "Bad prefix length: %s", arg);
	nat64lsn_apply_mask(af, prefix, *plen);
	free(p);
}