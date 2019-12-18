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
struct prison {int pr_flags; int pr_ip6s; struct in6_addr* pr_ip6; struct prison* pr_parent; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IN6_ARE_ADDR_EQUAL (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PRISON ; 
 int PR_IP6_USER ; 
 int /*<<< orphan*/  bcopy (struct in6_addr*,struct in6_addr*,int) ; 
 int /*<<< orphan*/  free (struct in6_addr*,int /*<<< orphan*/ ) ; 
 struct in6_addr* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prison_qcmp_v6 (struct in6_addr*,struct in6_addr*) ; 

int
prison_restrict_ip6(struct prison *pr, struct in6_addr *newip6)
{
	int ii, ij, used;
	struct prison *ppr;

	ppr = pr->pr_parent;
	if (!(pr->pr_flags & PR_IP6_USER)) {
		/* This has no user settings, so just copy the parent's list. */
		if (pr->pr_ip6s < ppr->pr_ip6s) {
			/*
			 * There's no room for the parent's list.  Use the
			 * new list buffer, which is assumed to be big enough
			 * (if it was passed).  If there's no buffer, try to
			 * allocate one.
			 */
			used = 1;
			if (newip6 == NULL) {
				newip6 = malloc(ppr->pr_ip6s * sizeof(*newip6),
				    M_PRISON, M_NOWAIT);
				if (newip6 != NULL)
					used = 0;
			}
			if (newip6 != NULL) {
				bcopy(ppr->pr_ip6, newip6,
				    ppr->pr_ip6s * sizeof(*newip6));
				free(pr->pr_ip6, M_PRISON);
				pr->pr_ip6 = newip6;
				pr->pr_ip6s = ppr->pr_ip6s;
			}
			return (used);
		}
		pr->pr_ip6s = ppr->pr_ip6s;
		if (pr->pr_ip6s > 0)
			bcopy(ppr->pr_ip6, pr->pr_ip6,
			    pr->pr_ip6s * sizeof(*newip6));
		else if (pr->pr_ip6 != NULL) {
			free(pr->pr_ip6, M_PRISON);
			pr->pr_ip6 = NULL;
		}
	} else if (pr->pr_ip6s > 0) {
		/* Remove addresses that aren't in the parent. */
		for (ij = 0; ij < ppr->pr_ip6s; ij++)
			if (IN6_ARE_ADDR_EQUAL(&pr->pr_ip6[0],
			    &ppr->pr_ip6[ij]))
				break;
		if (ij < ppr->pr_ip6s)
			ii = 1;
		else {
			bcopy(pr->pr_ip6 + 1, pr->pr_ip6,
			    --pr->pr_ip6s * sizeof(*pr->pr_ip6));
			ii = 0;
		}
		for (ij = 1; ii < pr->pr_ip6s; ) {
			if (IN6_ARE_ADDR_EQUAL(&pr->pr_ip6[ii],
			    &ppr->pr_ip6[0])) {
				ii++;
				continue;
			}
			switch (ij >= ppr->pr_ip6s ? -1 :
				prison_qcmp_v6(&pr->pr_ip6[ii], &ppr->pr_ip6[ij])) {
			case -1:
				bcopy(pr->pr_ip6 + ii + 1, pr->pr_ip6 + ii,
				    (--pr->pr_ip6s - ii) * sizeof(*pr->pr_ip6));
				break;
			case 0:
				ii++;
				ij++;
				break;
			case 1:
				ij++;
				break;
			}
		}
		if (pr->pr_ip6s == 0) {
			free(pr->pr_ip6, M_PRISON);
			pr->pr_ip6 = NULL;
		}
	}
	return 0;
}