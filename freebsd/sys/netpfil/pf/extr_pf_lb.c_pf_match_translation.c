#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct pfi_kif {int dummy; } ;
struct pf_ruleset {int dummy; } ;
struct pf_addr_wrap {int dummy; } ;
struct pf_rule_addr {int /*<<< orphan*/ * port; scalar_t__ port_op; int /*<<< orphan*/  neg; struct pf_addr_wrap addr; } ;
struct TYPE_12__ {TYPE_3__* cur; } ;
struct pf_rule {scalar_t__ action; scalar_t__ ifnot; int direction; scalar_t__ proto; scalar_t__ os_fingerprint; int tag; int rtableid; int /*<<< orphan*/ * anchor; scalar_t__ match_tag; TYPE_5__* skip; struct pf_rule_addr src; scalar_t__ af; int /*<<< orphan*/  kif; int /*<<< orphan*/  evaluations; struct pf_rule_addr dst; TYPE_4__ rpool; } ;
struct TYPE_15__ {int /*<<< orphan*/  tcp; } ;
struct pf_pdesc {scalar_t__ proto; TYPE_7__ hdr; TYPE_6__* pf_mtag; scalar_t__ af; } ;
struct pf_anchor_stackframe {int dummy; } ;
struct pf_addr {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_16__ {TYPE_2__* rules; } ;
struct TYPE_14__ {int /*<<< orphan*/  tag; } ;
struct TYPE_13__ {struct pf_rule* ptr; } ;
struct TYPE_11__ {struct pf_addr_wrap addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {TYPE_1__ active; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  M_GETFIB (struct mbuf*) ; 
 int /*<<< orphan*/  M_SETFIB (struct mbuf*,int) ; 
 scalar_t__ PF_BINAT ; 
 int PF_IN ; 
 scalar_t__ PF_MISMATCHAW (struct pf_addr_wrap*,struct pf_addr*,scalar_t__,int /*<<< orphan*/ ,struct pfi_kif*,int /*<<< orphan*/ ) ; 
 scalar_t__ PF_NOBINAT ; 
 scalar_t__ PF_NONAT ; 
 scalar_t__ PF_NORDR ; 
 scalar_t__ PF_OSFP_ANY ; 
 size_t PF_SKIP_AF ; 
 size_t PF_SKIP_DIR ; 
 size_t PF_SKIP_DST_ADDR ; 
 size_t PF_SKIP_DST_PORT ; 
 size_t PF_SKIP_IFP ; 
 size_t PF_SKIP_PROTO ; 
 size_t PF_SKIP_SRC_ADDR ; 
 size_t PF_SKIP_SRC_PORT ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 struct pf_rule* TAILQ_NEXT (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 TYPE_8__ pf_main_ruleset ; 
 int /*<<< orphan*/  pf_match_port (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_match_tag (struct mbuf*,struct pf_rule*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_osfp_fingerprint (struct pf_pdesc*,struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_osfp_match (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pf_step_into_anchor (struct pf_anchor_stackframe*,int*,struct pf_ruleset**,int,struct pf_rule**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_step_out_of_anchor (struct pf_anchor_stackframe*,int*,struct pf_ruleset**,int,struct pf_rule**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pf_tag_packet (struct mbuf*,struct pf_pdesc*,int) ; 
 scalar_t__ pfi_kif_match (int /*<<< orphan*/ ,struct pfi_kif*) ; 

__attribute__((used)) static struct pf_rule *
pf_match_translation(struct pf_pdesc *pd, struct mbuf *m, int off,
    int direction, struct pfi_kif *kif, struct pf_addr *saddr, u_int16_t sport,
    struct pf_addr *daddr, uint16_t dport, int rs_num,
    struct pf_anchor_stackframe *anchor_stack)
{
	struct pf_rule		*r, *rm = NULL;
	struct pf_ruleset	*ruleset = NULL;
	int			 tag = -1;
	int			 rtableid = -1;
	int			 asd = 0;

	r = TAILQ_FIRST(pf_main_ruleset.rules[rs_num].active.ptr);
	while (r && rm == NULL) {
		struct pf_rule_addr	*src = NULL, *dst = NULL;
		struct pf_addr_wrap	*xdst = NULL;

		if (r->action == PF_BINAT && direction == PF_IN) {
			src = &r->dst;
			if (r->rpool.cur != NULL)
				xdst = &r->rpool.cur->addr;
		} else {
			src = &r->src;
			dst = &r->dst;
		}

		r->evaluations++;
		if (pfi_kif_match(r->kif, kif) == r->ifnot)
			r = r->skip[PF_SKIP_IFP].ptr;
		else if (r->direction && r->direction != direction)
			r = r->skip[PF_SKIP_DIR].ptr;
		else if (r->af && r->af != pd->af)
			r = r->skip[PF_SKIP_AF].ptr;
		else if (r->proto && r->proto != pd->proto)
			r = r->skip[PF_SKIP_PROTO].ptr;
		else if (PF_MISMATCHAW(&src->addr, saddr, pd->af,
		    src->neg, kif, M_GETFIB(m)))
			r = r->skip[src == &r->src ? PF_SKIP_SRC_ADDR :
			    PF_SKIP_DST_ADDR].ptr;
		else if (src->port_op && !pf_match_port(src->port_op,
		    src->port[0], src->port[1], sport))
			r = r->skip[src == &r->src ? PF_SKIP_SRC_PORT :
			    PF_SKIP_DST_PORT].ptr;
		else if (dst != NULL &&
		    PF_MISMATCHAW(&dst->addr, daddr, pd->af, dst->neg, NULL,
		    M_GETFIB(m)))
			r = r->skip[PF_SKIP_DST_ADDR].ptr;
		else if (xdst != NULL && PF_MISMATCHAW(xdst, daddr, pd->af,
		    0, NULL, M_GETFIB(m)))
			r = TAILQ_NEXT(r, entries);
		else if (dst != NULL && dst->port_op &&
		    !pf_match_port(dst->port_op, dst->port[0],
		    dst->port[1], dport))
			r = r->skip[PF_SKIP_DST_PORT].ptr;
		else if (r->match_tag && !pf_match_tag(m, r, &tag,
		    pd->pf_mtag ? pd->pf_mtag->tag : 0))
			r = TAILQ_NEXT(r, entries);
		else if (r->os_fingerprint != PF_OSFP_ANY && (pd->proto !=
		    IPPROTO_TCP || !pf_osfp_match(pf_osfp_fingerprint(pd, m,
		    off, pd->hdr.tcp), r->os_fingerprint)))
			r = TAILQ_NEXT(r, entries);
		else {
			if (r->tag)
				tag = r->tag;
			if (r->rtableid >= 0)
				rtableid = r->rtableid;
			if (r->anchor == NULL) {
				rm = r;
			} else
				pf_step_into_anchor(anchor_stack, &asd,
				    &ruleset, rs_num, &r, NULL, NULL);
		}
		if (r == NULL)
			pf_step_out_of_anchor(anchor_stack, &asd, &ruleset,
			    rs_num, &r, NULL, NULL);
	}

	if (tag > 0 && pf_tag_packet(m, pd, tag))
		return (NULL);
	if (rtableid >= 0)
		M_SETFIB(m, rtableid);

	if (rm != NULL && (rm->action == PF_NONAT ||
	    rm->action == PF_NORDR || rm->action == PF_NOBINAT))
		return (NULL);
	return (rm);
}