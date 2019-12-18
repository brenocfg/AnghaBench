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
typedef  scalar_t__ u_int ;
struct tcpcb {int t_flags; int rcv_numsacks; scalar_t__ t_maxseg; int /*<<< orphan*/  t_state; } ;

/* Variables and functions */
 scalar_t__ PAD (scalar_t__) ; 
 scalar_t__ TCPOLEN_MAXSEG ; 
 int TCPOLEN_SACK ; 
 scalar_t__ TCPOLEN_SACKHDR ; 
 scalar_t__ TCPOLEN_SACK_PERMITTED ; 
 scalar_t__ TCPOLEN_SIGNATURE ; 
 scalar_t__ TCPOLEN_TSTAMP_APPA ; 
 scalar_t__ TCPOLEN_WINDOW ; 
 scalar_t__ TCPS_HAVEESTABLISHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MAXOLEN ; 
 int TF_NOOPT ; 
 int TF_RCVD_TSTMP ; 
 int TF_REQ_SCALE ; 
 int TF_REQ_TSTMP ; 
 int TF_SACK_PERMIT ; 
 int TF_SIGNATURE ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

u_int
tcp_maxseg(const struct tcpcb *tp)
{
	u_int optlen;

	if (tp->t_flags & TF_NOOPT)
		return (tp->t_maxseg);

	/*
	 * Here we have a simplified code from tcp_addoptions(),
	 * without a proper loop, and having most of paddings hardcoded.
	 * We might make mistakes with padding here in some edge cases,
	 * but this is harmless, since result of tcp_maxseg() is used
	 * only in cwnd and ssthresh estimations.
	 */
#define	PAD(len)	((((len) / 4) + !!((len) % 4)) * 4)
	if (TCPS_HAVEESTABLISHED(tp->t_state)) {
		if (tp->t_flags & TF_RCVD_TSTMP)
			optlen = TCPOLEN_TSTAMP_APPA;
		else
			optlen = 0;
#if defined(IPSEC_SUPPORT) || defined(TCP_SIGNATURE)
		if (tp->t_flags & TF_SIGNATURE)
			optlen += PAD(TCPOLEN_SIGNATURE);
#endif
		if ((tp->t_flags & TF_SACK_PERMIT) && tp->rcv_numsacks > 0) {
			optlen += TCPOLEN_SACKHDR;
			optlen += tp->rcv_numsacks * TCPOLEN_SACK;
			optlen = PAD(optlen);
		}
	} else {
		if (tp->t_flags & TF_REQ_TSTMP)
			optlen = TCPOLEN_TSTAMP_APPA;
		else
			optlen = PAD(TCPOLEN_MAXSEG);
		if (tp->t_flags & TF_REQ_SCALE)
			optlen += PAD(TCPOLEN_WINDOW);
#if defined(IPSEC_SUPPORT) || defined(TCP_SIGNATURE)
		if (tp->t_flags & TF_SIGNATURE)
			optlen += PAD(TCPOLEN_SIGNATURE);
#endif
		if (tp->t_flags & TF_SACK_PERMIT)
			optlen += PAD(TCPOLEN_SACK_PERMITTED);
	}
#undef PAD
	optlen = min(optlen, TCP_MAXOLEN);
	return (tp->t_maxseg - optlen);
}