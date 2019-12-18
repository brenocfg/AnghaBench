#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inpcbgroup {int dummy; } ;
struct inpcb {int inp_flags2; size_t inp_rss_listen_bucket; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  in6p_laddr; TYPE_1__* inp_pcbinfo; } ;
struct TYPE_2__ {struct inpcbgroup* ipi_pcbgroups; } ;

/* Variables and functions */
 int INP_RSS_BUCKET_SET ; 
 struct inpcbgroup* in6_pcbgroup_bytuple (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct inpcbgroup *
in6_pcbgroup_byinpcb(struct inpcb *inp)
{

#ifdef	RSS
	/*
	 * Listen sockets with INP_RSS_BUCKET_SET set have a pre-determined
	 * RSS bucket and thus we should use this pcbgroup, rather than
	 * using a tuple or hash.
	 *
	 * XXX should verify that there's actually pcbgroups and inp_rss_listen_bucket
	 * fits in that!
	 */
	if (inp->inp_flags2 & INP_RSS_BUCKET_SET)
		return (&inp->inp_pcbinfo->ipi_pcbgroups[inp->inp_rss_listen_bucket]);
#endif

	return (in6_pcbgroup_bytuple(inp->inp_pcbinfo, &inp->in6p_laddr,
	    inp->inp_lport, &inp->in6p_faddr, inp->inp_fport));
}