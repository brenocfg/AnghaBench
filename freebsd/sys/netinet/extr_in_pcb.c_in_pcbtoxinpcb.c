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
struct xinpcb {int xi_len; uintptr_t inp_ppcb; int /*<<< orphan*/  inp_ip_minttl; int /*<<< orphan*/  inp_ip_p; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_ip_tos; int /*<<< orphan*/  in6p_hops; int /*<<< orphan*/  in6p_cksum; int /*<<< orphan*/  inp_rss_listen_bucket; int /*<<< orphan*/  inp_flags2; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_flowtype; int /*<<< orphan*/  inp_flowid; int /*<<< orphan*/  inp_flow; int /*<<< orphan*/  inp_gencnt; int /*<<< orphan*/  inp_inc; int /*<<< orphan*/  xi_socket; } ;
struct inpcb {int /*<<< orphan*/  inp_ip_minttl; int /*<<< orphan*/  inp_ip_p; int /*<<< orphan*/  inp_ip_ttl; int /*<<< orphan*/  inp_vflag; int /*<<< orphan*/  inp_ip_tos; int /*<<< orphan*/  in6p_hops; int /*<<< orphan*/  in6p_cksum; int /*<<< orphan*/  inp_rss_listen_bucket; int /*<<< orphan*/  inp_flags2; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_flowtype; int /*<<< orphan*/  inp_flowid; int /*<<< orphan*/  inp_flow; scalar_t__ inp_ppcb; int /*<<< orphan*/  inp_gencnt; int /*<<< orphan*/  inp_inc; scalar_t__ inp_socket; } ;
struct in_conninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct xinpcb*,int) ; 
 int /*<<< orphan*/  sotoxsocket (scalar_t__,int /*<<< orphan*/ *) ; 

void
in_pcbtoxinpcb(const struct inpcb *inp, struct xinpcb *xi)
{

	bzero(xi, sizeof(*xi));
	xi->xi_len = sizeof(struct xinpcb);
	if (inp->inp_socket)
		sotoxsocket(inp->inp_socket, &xi->xi_socket);
	bcopy(&inp->inp_inc, &xi->inp_inc, sizeof(struct in_conninfo));
	xi->inp_gencnt = inp->inp_gencnt;
	xi->inp_ppcb = (uintptr_t)inp->inp_ppcb;
	xi->inp_flow = inp->inp_flow;
	xi->inp_flowid = inp->inp_flowid;
	xi->inp_flowtype = inp->inp_flowtype;
	xi->inp_flags = inp->inp_flags;
	xi->inp_flags2 = inp->inp_flags2;
	xi->inp_rss_listen_bucket = inp->inp_rss_listen_bucket;
	xi->in6p_cksum = inp->in6p_cksum;
	xi->in6p_hops = inp->in6p_hops;
	xi->inp_ip_tos = inp->inp_ip_tos;
	xi->inp_vflag = inp->inp_vflag;
	xi->inp_ip_ttl = inp->inp_ip_ttl;
	xi->inp_ip_p = inp->inp_ip_p;
	xi->inp_ip_minttl = inp->inp_ip_minttl;
}