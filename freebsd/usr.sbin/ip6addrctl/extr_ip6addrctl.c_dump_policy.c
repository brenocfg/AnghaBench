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
struct sockaddr {int dummy; } ;
struct in6_addrpolicy {int preced; int label; scalar_t__ use; int /*<<< orphan*/  addrmask; int /*<<< orphan*/  addr; } ;
struct policyqueue {struct in6_addrpolicy pc_policy; } ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 struct policyqueue* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct policyqueue* TAILQ_NEXT (struct policyqueue*,int /*<<< orphan*/ ) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mask2plen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pc_entry ; 
 int /*<<< orphan*/  policyhead ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
dump_policy(void)
{
	size_t addrlen;
	char addrbuf[NI_MAXHOST];
	struct in6_addrpolicy *pol;
	struct policyqueue *ent;
	int plen, first = 1;

	for (ent = TAILQ_FIRST(&policyhead); ent;
	     ent = TAILQ_NEXT(ent, pc_entry)) {
		pol = &ent->pc_policy;
		if (first) {
			printf("%-30s %5s %5s %8s\n",
			       "Prefix", "Prec", "Label", "Use");
			first = 0;
		}

		if ((getnameinfo((struct sockaddr *)&pol->addr,
				 sizeof(pol->addr), addrbuf, sizeof(addrbuf),
				 NULL, 0, NI_NUMERICHOST))) {
			warnx("getnameinfo for prefix address failed");
			continue;
		}
		if ((plen = mask2plen(&pol->addrmask)) < 0) {
			warnx("invalid address mask");
			continue;
		}
		addrlen = strlen(addrbuf);
		if (addrlen + sizeof("/128") < sizeof(addrbuf)) {
			snprintf(&addrbuf[addrlen],
				 sizeof(addrbuf) - addrlen - 1,
				 "/%d", plen);
			printf("%-30s", addrbuf);
		} else		/* XXX */
			printf("%s/%d", addrbuf, plen);
		printf(" %5d %5d %8llu\n", pol->preced, pol->label,
		    (unsigned long long)pol->use);
	}
}