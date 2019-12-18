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
struct tcphdr {int /*<<< orphan*/  th_ack; } ;
struct tcpcb {scalar_t__ t_state; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  snd_una; } ;
struct mbuf {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BANDLIM_RST_OPENPORT ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_SYN_RECEIVED ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int TH_ACK ; 
 int /*<<< orphan*/  ctf_do_dropwithreset (struct mbuf*,struct tcpcb*,struct tcphdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

void
ctf_do_dropafterack(struct mbuf *m, struct tcpcb *tp, struct tcphdr *th, int32_t thflags, int32_t tlen, int32_t * ret_val)
{
	/*
	 * Generate an ACK dropping incoming segment if it occupies sequence
	 * space, where the ACK reflects our state.
	 *
	 * We can now skip the test for the RST flag since all paths to this
	 * code happen after packets containing RST have been dropped.
	 *
	 * In the SYN-RECEIVED state, don't send an ACK unless the segment
	 * we received passes the SYN-RECEIVED ACK test. If it fails send a
	 * RST.  This breaks the loop in the "LAND" DoS attack, and also
	 * prevents an ACK storm between two listening ports that have been
	 * sent forged SYN segments, each with the source address of the
	 * other.
	 */
	if (tp->t_state == TCPS_SYN_RECEIVED && (thflags & TH_ACK) &&
	    (SEQ_GT(tp->snd_una, th->th_ack) ||
	    SEQ_GT(th->th_ack, tp->snd_max))) {
		*ret_val = 1;
		ctf_do_dropwithreset(m, tp, th, BANDLIM_RST_OPENPORT, tlen);
		return;
	} else
		*ret_val = 0;
	tp->t_flags |= TF_ACKNOW;
	if (m)
		m_freem(m);
}