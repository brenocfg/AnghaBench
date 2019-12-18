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
struct numa_policy {int policy; int /*<<< orphan*/ * name; } ;
struct bitset {int dummy; } ;
typedef  int /*<<< orphan*/  rootmask ;
typedef  int /*<<< orphan*/  domainset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_ROOT ; 
 int /*<<< orphan*/  CPU_WHICH_PID ; 
 int /*<<< orphan*/  DOMAINSET_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_SETSIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ cpuset_getdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  parselist (char*,struct bitset*,int /*<<< orphan*/ ) ; 
 struct numa_policy* policies ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parsedomainlist(char *list, domainset_t *mask, int *policyp)
{
	domainset_t rootmask;
	struct numa_policy *policy;
	char *l;
	int p;

	/*
	 * Use the rootset's policy as the default for unspecified policies.
	 */
	if (cpuset_getdomain(CPU_LEVEL_ROOT, CPU_WHICH_PID, -1,
	    sizeof(rootmask), &rootmask, &p) != 0)
		err(EXIT_FAILURE, "getdomain");

	l = list;
	for (policy = &policies[0]; policy->name != NULL; policy++) {
		if (strncasecmp(l, policy->name, strlen(policy->name)) == 0) {
			p = policy->policy;
			l += strlen(policy->name);
			if (*l != ':' && *l != '\0')
				errx(EXIT_FAILURE, "Malformed list %s", list);
			if (*l == ':')
				l++;
			break;
		}
	}
	*policyp = p;
	if (strcasecmp(l, "all") == 0 || *l == '\0') {
		DOMAINSET_COPY(&rootmask, mask);
		return;
	}
	parselist(l, (struct bitset *)mask, DOMAINSET_SETSIZE);
}