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
struct in6_addrpolicy {int dummy; } ;
struct policyqueue {struct in6_addrpolicy pc_policy; } ;

/* Variables and functions */
 int CTL_NET ; 
 int IPPROTO_IPV6 ; 
 int IPV6CTL_ADDRCTLPOLICY ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct in6_addrpolicy*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/  pc_entry ; 
 int /*<<< orphan*/  policyhead ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,struct in6_addrpolicy*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_policy(void)
{
	int mib[] = { CTL_NET, PF_INET6, IPPROTO_IPV6, IPV6CTL_ADDRCTLPOLICY };
	size_t l;
	struct in6_addrpolicy *buf;
	struct in6_addrpolicy *pol, *ep;

	if (sysctl(mib, nitems(mib), NULL, &l, NULL, 0) < 0) {
		err(1, "sysctl(IPV6CTL_ADDRCTLPOLICY)");
		/* NOTREACHED */
	}
	if (l == 0) {
		printf("no source-address-selection policy is installed\n");
		return;
	}
	if ((buf = malloc(l)) == NULL) {
		errx(1, "malloc failed");
		/* NOTREACHED */
	}
	if (sysctl(mib, nitems(mib), buf, &l, NULL, 0) < 0) {
		err(1, "sysctl(IPV6CTL_ADDRCTLPOLICY)");
		/* NOTREACHED */
	}

	ep = buf + l/sizeof(*buf);
	for (pol = buf; pol + 1 <= ep; pol++) {
		struct policyqueue *new;

		if ((new = malloc(sizeof(*new))) == NULL)
			errx(1, "malloc failed\n");
		new->pc_policy = *pol;
		TAILQ_INSERT_TAIL(&policyhead, new, pc_entry);
	}

	free(buf);
}