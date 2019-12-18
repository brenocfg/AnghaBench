#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/ * td_ucred; } ;
struct sockopt {struct thread* sopt_td; } ;
struct socket {TYPE_2__* so_proto; } ;
struct mbuf {scalar_t__ m_len; } ;
struct TYPE_3__ {scalar_t__ ip6po_rhi_rthdr; } ;
struct ip6_pktopts {TYPE_1__ ip6po_rhinfo; scalar_t__ ip6po_dest2; scalar_t__ ip6po_dest1; scalar_t__ ip6po_hbh; scalar_t__ ip6po_nexthop; scalar_t__ ip6po_pktinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  pr_protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IP6OPT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (struct ip6_pktopts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_clearpktopts (struct ip6_pktopts*,int) ; 
 int ip6_setpktopts (struct mbuf*,struct ip6_pktopts*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip6_pktopts* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ip6_pcbopts(struct ip6_pktopts **pktopt, struct mbuf *m,
    struct socket *so, struct sockopt *sopt)
{
	struct ip6_pktopts *opt = *pktopt;
	int error = 0;
	struct thread *td = sopt->sopt_td;

	/* turn off any old options. */
	if (opt) {
#ifdef DIAGNOSTIC
		if (opt->ip6po_pktinfo || opt->ip6po_nexthop ||
		    opt->ip6po_hbh || opt->ip6po_dest1 || opt->ip6po_dest2 ||
		    opt->ip6po_rhinfo.ip6po_rhi_rthdr)
			printf("ip6_pcbopts: all specified options are cleared.\n");
#endif
		ip6_clearpktopts(opt, -1);
	} else
		opt = malloc(sizeof(*opt), M_IP6OPT, M_WAITOK);
	*pktopt = NULL;

	if (!m || m->m_len == 0) {
		/*
		 * Only turning off any previous options, regardless of
		 * whether the opt is just created or given.
		 */
		free(opt, M_IP6OPT);
		return (0);
	}

	/*  set options specified by user. */
	if ((error = ip6_setpktopts(m, opt, NULL, (td != NULL) ?
	    td->td_ucred : NULL, so->so_proto->pr_protocol)) != 0) {
		ip6_clearpktopts(opt, -1); /* XXX: discard all options */
		free(opt, M_IP6OPT);
		return (error);
	}
	*pktopt = opt;
	return (0);
}