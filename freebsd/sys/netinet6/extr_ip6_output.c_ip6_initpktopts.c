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
struct ip6_pktopts {int ip6po_hlim; int ip6po_tclass; int /*<<< orphan*/  ip6po_prefer_tempaddr; int /*<<< orphan*/  ip6po_minmtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6PO_MINMTU_MCASTONLY ; 
 int /*<<< orphan*/  IP6PO_TEMPADDR_SYSTEM ; 
 int /*<<< orphan*/  bzero (struct ip6_pktopts*,int) ; 

void
ip6_initpktopts(struct ip6_pktopts *opt)
{

	bzero(opt, sizeof(*opt));
	opt->ip6po_hlim = -1;	/* -1 means default hop limit */
	opt->ip6po_tclass = -1;	/* -1 means default traffic class */
	opt->ip6po_minmtu = IP6PO_MINMTU_MCASTONLY;
	opt->ip6po_prefer_tempaddr = IP6PO_TEMPADDR_SYSTEM;
}