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
struct bitset {int dummy; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  domainset_t ;
typedef  int /*<<< orphan*/  domain ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETSIZE ; 
 int /*<<< orphan*/  DOMAINSET_SETSIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ cpuset_getaffinity (size_t,size_t,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpuset_getdomain (size_t,size_t,scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ id ; 
 size_t level ; 
 int /*<<< orphan*/ * levelnames ; 
 int /*<<< orphan*/ * policynames ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printset (struct bitset*,int /*<<< orphan*/ ) ; 
 size_t which ; 
 char** whichnames ; 

__attribute__((used)) static void
printaffinity(void)
{
	domainset_t domain;
	cpuset_t mask;
	int policy;

	if (cpuset_getaffinity(level, which, id, sizeof(mask), &mask) != 0)
		err(EXIT_FAILURE, "getaffinity");
	printf("%s %jd%s mask: ", whichnames[which], (intmax_t)id,
	    levelnames[level]);
	printset((struct bitset *)&mask, CPU_SETSIZE);
	if (dflag)
		goto out;
	if (cpuset_getdomain(level, which, id, sizeof(domain), &domain,
	    &policy) != 0)
		err(EXIT_FAILURE, "getdomain");
	printf("%s %jd%s domain policy: %s mask: ", whichnames[which],
	    (intmax_t)id, levelnames[level], policynames[policy]);
	printset((struct bitset *)&domain, DOMAINSET_SETSIZE);
out:
	exit(EXIT_SUCCESS);
}