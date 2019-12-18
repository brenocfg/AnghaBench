#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct tcphdr {int th_flags; int th_off; scalar_t__ th_x2; scalar_t__ th_urp; void* th_sum; int /*<<< orphan*/  th_ack; int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; } ;
struct pfi_kif {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * port; scalar_t__ port_op; int /*<<< orphan*/  neg; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int /*<<< orphan*/ * port; scalar_t__ port_op; int /*<<< orphan*/  neg; int /*<<< orphan*/  addr; } ;
struct pf_rule {scalar_t__ ifnot; int direction; scalar_t__ af; scalar_t__ proto; scalar_t__ os_fingerprint; scalar_t__ action; int rule_flag; scalar_t__ log; scalar_t__ max_mss; int /*<<< orphan*/ * bytes; int /*<<< orphan*/ * packets; TYPE_6__* skip; TYPE_5__ dst; TYPE_4__ src; int /*<<< orphan*/  kif; int /*<<< orphan*/  evaluations; } ;
struct TYPE_8__ {struct tcphdr* tcp; } ;
struct pf_pdesc {scalar_t__ af; scalar_t__ proto; int /*<<< orphan*/  flags; scalar_t__ tot_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ hdr; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ sa_family_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_14__ {TYPE_3__* rules; } ;
struct TYPE_13__ {struct pf_rule* ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {TYPE_2__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  M_GETFIB (struct mbuf*) ; 
 int /*<<< orphan*/  PFDESC_TCP_NORM ; 
 int /*<<< orphan*/  PFLOG_PACKET (struct pfi_kif*,struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct pf_rule*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pf_pdesc*,int) ; 
 int /*<<< orphan*/  PFRES_NORM ; 
 int PFRULE_REASSEMBLE_TCP ; 
 int PF_DROP ; 
 scalar_t__ PF_MISMATCHAW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct pfi_kif*,int /*<<< orphan*/ ) ; 
 scalar_t__ PF_NOSCRUB ; 
 scalar_t__ PF_OSFP_ANY ; 
 int PF_OUT ; 
 int PF_PASS ; 
 size_t PF_RULESET_SCRUB ; 
 int /*<<< orphan*/  PF_RULES_RASSERT () ; 
 size_t PF_SKIP_AF ; 
 size_t PF_SKIP_DIR ; 
 size_t PF_SKIP_DST_ADDR ; 
 size_t PF_SKIP_DST_PORT ; 
 size_t PF_SKIP_IFP ; 
 size_t PF_SKIP_PROTO ; 
 size_t PF_SKIP_SRC_ADDR ; 
 size_t PF_SKIP_SRC_PORT ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 struct pf_rule* TAILQ_NEXT (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int TH_ACK ; 
 int TH_FIN ; 
 int TH_PUSH ; 
 int TH_RST ; 
 int TH_SYN ; 
 int TH_URG ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_7__ pf_main_ruleset ; 
 int /*<<< orphan*/  pf_match_port (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pf_normalize_tcpopt (struct pf_rule*,struct mbuf*,struct tcphdr*,int,scalar_t__) ; 
 int /*<<< orphan*/  pf_osfp_fingerprint (struct pf_pdesc*,struct mbuf*,int,struct tcphdr*) ; 
 int /*<<< orphan*/  pf_osfp_match (int /*<<< orphan*/ ,scalar_t__) ; 
 void* pf_proto_cksum_fixup (struct mbuf*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pfi_kif_match (int /*<<< orphan*/ ,struct pfi_kif*) ; 

int
pf_normalize_tcp(int dir, struct pfi_kif *kif, struct mbuf *m, int ipoff,
    int off, void *h, struct pf_pdesc *pd)
{
	struct pf_rule	*r, *rm = NULL;
	struct tcphdr	*th = pd->hdr.tcp;
	int		 rewrite = 0;
	u_short		 reason;
	u_int8_t	 flags;
	sa_family_t	 af = pd->af;

	PF_RULES_RASSERT();

	r = TAILQ_FIRST(pf_main_ruleset.rules[PF_RULESET_SCRUB].active.ptr);
	while (r != NULL) {
		r->evaluations++;
		if (pfi_kif_match(r->kif, kif) == r->ifnot)
			r = r->skip[PF_SKIP_IFP].ptr;
		else if (r->direction && r->direction != dir)
			r = r->skip[PF_SKIP_DIR].ptr;
		else if (r->af && r->af != af)
			r = r->skip[PF_SKIP_AF].ptr;
		else if (r->proto && r->proto != pd->proto)
			r = r->skip[PF_SKIP_PROTO].ptr;
		else if (PF_MISMATCHAW(&r->src.addr, pd->src, af,
		    r->src.neg, kif, M_GETFIB(m)))
			r = r->skip[PF_SKIP_SRC_ADDR].ptr;
		else if (r->src.port_op && !pf_match_port(r->src.port_op,
			    r->src.port[0], r->src.port[1], th->th_sport))
			r = r->skip[PF_SKIP_SRC_PORT].ptr;
		else if (PF_MISMATCHAW(&r->dst.addr, pd->dst, af,
		    r->dst.neg, NULL, M_GETFIB(m)))
			r = r->skip[PF_SKIP_DST_ADDR].ptr;
		else if (r->dst.port_op && !pf_match_port(r->dst.port_op,
			    r->dst.port[0], r->dst.port[1], th->th_dport))
			r = r->skip[PF_SKIP_DST_PORT].ptr;
		else if (r->os_fingerprint != PF_OSFP_ANY && !pf_osfp_match(
			    pf_osfp_fingerprint(pd, m, off, th),
			    r->os_fingerprint))
			r = TAILQ_NEXT(r, entries);
		else {
			rm = r;
			break;
		}
	}

	if (rm == NULL || rm->action == PF_NOSCRUB)
		return (PF_PASS);
	else {
		r->packets[dir == PF_OUT]++;
		r->bytes[dir == PF_OUT] += pd->tot_len;
	}

	if (rm->rule_flag & PFRULE_REASSEMBLE_TCP)
		pd->flags |= PFDESC_TCP_NORM;

	flags = th->th_flags;
	if (flags & TH_SYN) {
		/* Illegal packet */
		if (flags & TH_RST)
			goto tcp_drop;

		if (flags & TH_FIN)
			goto tcp_drop;
	} else {
		/* Illegal packet */
		if (!(flags & (TH_ACK|TH_RST)))
			goto tcp_drop;
	}

	if (!(flags & TH_ACK)) {
		/* These flags are only valid if ACK is set */
		if ((flags & TH_FIN) || (flags & TH_PUSH) || (flags & TH_URG))
			goto tcp_drop;
	}

	/* Check for illegal header length */
	if (th->th_off < (sizeof(struct tcphdr) >> 2))
		goto tcp_drop;

	/* If flags changed, or reserved data set, then adjust */
	if (flags != th->th_flags || th->th_x2 != 0) {
		u_int16_t	ov, nv;

		ov = *(u_int16_t *)(&th->th_ack + 1);
		th->th_flags = flags;
		th->th_x2 = 0;
		nv = *(u_int16_t *)(&th->th_ack + 1);

		th->th_sum = pf_proto_cksum_fixup(m, th->th_sum, ov, nv, 0);
		rewrite = 1;
	}

	/* Remove urgent pointer, if TH_URG is not set */
	if (!(flags & TH_URG) && th->th_urp) {
		th->th_sum = pf_proto_cksum_fixup(m, th->th_sum, th->th_urp,
		    0, 0);
		th->th_urp = 0;
		rewrite = 1;
	}

	/* Process options */
	if (r->max_mss && pf_normalize_tcpopt(r, m, th, off, pd->af))
		rewrite = 1;

	/* copy back packet headers if we sanitized */
	if (rewrite)
		m_copyback(m, off, sizeof(*th), (caddr_t)th);

	return (PF_PASS);

 tcp_drop:
	REASON_SET(&reason, PFRES_NORM);
	if (rm != NULL && r->log)
		PFLOG_PACKET(kif, m, AF_INET, dir, reason, r, NULL, NULL, pd,
		    1);
	return (PF_DROP);
}