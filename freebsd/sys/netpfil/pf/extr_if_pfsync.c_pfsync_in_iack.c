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
struct pfsync_pkt {int dummy; } ;
struct pfsync_ins_ack {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
struct pf_state {int state_flags; } ;
struct mbuf {scalar_t__ m_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfsyncs_badlen; } ;

/* Variables and functions */
 int PFSTATE_ACK ; 
 int /*<<< orphan*/  PF_STATE_UNLOCK (struct pf_state*) ; 
 TYPE_1__ V_pfsyncstats ; 
 struct mbuf* m_pulldown (struct mbuf*,int,int,int*) ; 
 struct pf_state* pf_find_state_byid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfsync_undefer_state (struct pf_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfsync_in_iack(struct pfsync_pkt *pkt, struct mbuf *m, int offset, int count)
{
	struct pfsync_ins_ack *ia, *iaa;
	struct pf_state *st;

	struct mbuf *mp;
	int len = count * sizeof(*ia);
	int offp, i;

	mp = m_pulldown(m, offset, len, &offp);
	if (mp == NULL) {
		V_pfsyncstats.pfsyncs_badlen++;
		return (-1);
	}
	iaa = (struct pfsync_ins_ack *)(mp->m_data + offp);

	for (i = 0; i < count; i++) {
		ia = &iaa[i];

		st = pf_find_state_byid(ia->id, ia->creatorid);
		if (st == NULL)
			continue;

		if (st->state_flags & PFSTATE_ACK) {
			pfsync_undefer_state(st, 0);
		}
		PF_STATE_UNLOCK(st);
	}
	/*
	 * XXX this is not yet implemented, but we know the size of the
	 * message so we can skip it.
	 */

	return (count * sizeof(struct pfsync_ins_ack));
}