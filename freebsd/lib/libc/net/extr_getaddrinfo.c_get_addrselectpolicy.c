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
struct policyhead {int dummy; } ;

/* Variables and functions */
 int CTL_NET ; 
 int IPPROTO_IPV6 ; 
 int IPV6CTL_ADDRCTLPOLICY ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct policyhead*,struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_addrselectpolicy (struct policyhead*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/  pc_entry ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_addrselectpolicy(struct policyhead *head)
{
#ifdef INET6
	int mib[] = { CTL_NET, PF_INET6, IPPROTO_IPV6, IPV6CTL_ADDRCTLPOLICY };
	size_t l;
	char *buf;
	struct in6_addrpolicy *pol, *ep;

	if (sysctl(mib, nitems(mib), NULL, &l, NULL, 0) < 0)
		return (0);
	if (l == 0)
		return (0);
	if ((buf = malloc(l)) == NULL)
		return (0);
	if (sysctl(mib, nitems(mib), buf, &l, NULL, 0) < 0) {
		free(buf);
		return (0);
	}

	ep = (struct in6_addrpolicy *)(buf + l);
	for (pol = (struct in6_addrpolicy *)buf; pol + 1 <= ep; pol++) {
		struct policyqueue *new;

		if ((new = malloc(sizeof(*new))) == NULL) {
			free_addrselectpolicy(head); /* make the list empty */
			break;
		}
		new->pc_policy = *pol;
		TAILQ_INSERT_TAIL(head, new, pc_entry);
	}

	free(buf);
	return (1);
#else
	return (0);
#endif
}