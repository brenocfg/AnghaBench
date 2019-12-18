#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t odd_even; size_t mss_idx; size_t wscale_idx; scalar_t__ sack_ok; } ;
union syncookie {int cookie; TYPE_2__ flags; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int tcp_seq ;
struct tcpopt {int to_flags; int /*<<< orphan*/  to_tsval; } ;
struct tcphdr {int th_ack; int th_seq; } ;
struct syncache_head {int dummy; } ;
struct syncache {int sc_irs; int sc_iss; int sc_flowlabel; int sc_requested_r_scale; int sc_wnd; scalar_t__ sc_rxmits; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_tsoff; int /*<<< orphan*/  sc_tsreflect; int /*<<< orphan*/  sc_requested_s_scale; int /*<<< orphan*/  sc_peer_mss; int /*<<< orphan*/  sc_ip_tos; int /*<<< orphan*/  sc_ip_ttl; int /*<<< orphan*/ * sc_ipopts; int /*<<< orphan*/  sc_inc; } ;
struct socket {int sol_sbrcv_hiwat; } ;
struct in_conninfo {int inc_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** key; } ;
struct TYPE_8__ {TYPE_1__ secret; } ;
struct TYPE_7__ {int inp_flags; int /*<<< orphan*/  inp_ip_tos; int /*<<< orphan*/  inp_ip_ttl; } ;

/* Variables and functions */
 int IN6P_AUTOFLOWLABEL ; 
#define  INC_ISIPV6 128 
 int IPV6_FLOWLABEL_MASK ; 
 int /*<<< orphan*/  SCF_SACK ; 
 int /*<<< orphan*/  SCF_SIGNATURE ; 
 int /*<<< orphan*/  SCF_TIMESTAMP ; 
 int /*<<< orphan*/  SCF_WINSCALE ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int TCP_MAXWIN ; 
 int TCP_MAX_WINSHIFT ; 
 int TOF_SIGNATURE ; 
 int TOF_TS ; 
 TYPE_4__ V_tcp_syncache ; 
 int /*<<< orphan*/  bcopy (struct in_conninfo*,int /*<<< orphan*/ *,int) ; 
 int imax (int,int /*<<< orphan*/ ) ; 
 int imin (int,int) ; 
 int sb_max ; 
 TYPE_3__* sotoinpcb (struct socket*) ; 
 int syncookie_mac (struct in_conninfo*,int,int,int /*<<< orphan*/ *,uintptr_t) ; 
 int /*<<< orphan*/  tcp_new_ts_offset (struct in_conninfo*) ; 
 int /*<<< orphan*/ * tcp_sc_msstab ; 
 int /*<<< orphan*/ * tcp_sc_wstab ; 
 int /*<<< orphan*/  tcps_sc_recvcookie ; 

__attribute__((used)) static struct syncache *
syncookie_lookup(struct in_conninfo *inc, struct syncache_head *sch, 
    struct syncache *sc, struct tcphdr *th, struct tcpopt *to,
    struct socket *lso)
{
	uint32_t hash;
	uint8_t *secbits;
	tcp_seq ack, seq;
	int wnd, wscale = 0;
	union syncookie cookie;

	/*
	 * Pull information out of SYN-ACK/ACK and revert sequence number
	 * advances.
	 */
	ack = th->th_ack - 1;
	seq = th->th_seq - 1;

	/*
	 * Unpack the flags containing enough information to restore the
	 * connection.
	 */
	cookie.cookie = (ack & 0xff) ^ (ack >> 24);

	/* Which of the two secrets to use. */
	secbits = V_tcp_syncache.secret.key[cookie.flags.odd_even];

	hash = syncookie_mac(inc, seq, cookie.cookie, secbits, (uintptr_t)sch);

	/* The recomputed hash matches the ACK if this was a genuine cookie. */
	if ((ack & ~0xff) != (hash & ~0xff))
		return (NULL);

	/* Fill in the syncache values. */
	sc->sc_flags = 0;
	bcopy(inc, &sc->sc_inc, sizeof(struct in_conninfo));
	sc->sc_ipopts = NULL;
	
	sc->sc_irs = seq;
	sc->sc_iss = ack;

	switch (inc->inc_flags & INC_ISIPV6) {
#ifdef INET
	case 0:
		sc->sc_ip_ttl = sotoinpcb(lso)->inp_ip_ttl;
		sc->sc_ip_tos = sotoinpcb(lso)->inp_ip_tos;
		break;
#endif
#ifdef INET6
	case INC_ISIPV6:
		if (sotoinpcb(lso)->inp_flags & IN6P_AUTOFLOWLABEL)
			sc->sc_flowlabel = sc->sc_iss & IPV6_FLOWLABEL_MASK;
		break;
#endif
	}

	sc->sc_peer_mss = tcp_sc_msstab[cookie.flags.mss_idx];

	/* We can simply recompute receive window scale we sent earlier. */
	while (wscale < TCP_MAX_WINSHIFT && (TCP_MAXWIN << wscale) < sb_max)
		wscale++;

	/* Only use wscale if it was enabled in the orignal SYN. */
	if (cookie.flags.wscale_idx > 0) {
		sc->sc_requested_r_scale = wscale;
		sc->sc_requested_s_scale = tcp_sc_wstab[cookie.flags.wscale_idx];
		sc->sc_flags |= SCF_WINSCALE;
	}

	wnd = lso->sol_sbrcv_hiwat;
	wnd = imax(wnd, 0);
	wnd = imin(wnd, TCP_MAXWIN);
	sc->sc_wnd = wnd;

	if (cookie.flags.sack_ok)
		sc->sc_flags |= SCF_SACK;

	if (to->to_flags & TOF_TS) {
		sc->sc_flags |= SCF_TIMESTAMP;
		sc->sc_tsreflect = to->to_tsval;
		sc->sc_tsoff = tcp_new_ts_offset(inc);
	}

	if (to->to_flags & TOF_SIGNATURE)
		sc->sc_flags |= SCF_SIGNATURE;

	sc->sc_rxmits = 0;

	TCPSTAT_INC(tcps_sc_recvcookie);
	return (sc);
}