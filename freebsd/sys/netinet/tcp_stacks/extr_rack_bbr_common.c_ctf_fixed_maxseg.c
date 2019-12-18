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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int t_flags; scalar_t__ t_maxseg; int /*<<< orphan*/  t_state; } ;

/* Variables and functions */
 int PAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPOLEN_MAXSEG ; 
 int /*<<< orphan*/  TCPOLEN_SACK_PERMITTED ; 
 int /*<<< orphan*/  TCPOLEN_SIGNATURE ; 
 int TCPOLEN_TSTAMP_APPA ; 
 int /*<<< orphan*/  TCPOLEN_WINDOW ; 
 scalar_t__ TCPS_HAVEESTABLISHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MAXOLEN ; 
 int TF_NOOPT ; 
 int TF_RCVD_TSTMP ; 
 int TF_REQ_SCALE ; 
 int TF_REQ_TSTMP ; 
 int TF_SACK_PERMIT ; 
 int TF_SIGNATURE ; 
 int min (int,int /*<<< orphan*/ ) ; 

uint32_t
ctf_fixed_maxseg(struct tcpcb *tp)
{
	int optlen;

	if (tp->t_flags & TF_NOOPT)
		return (tp->t_maxseg);

	/*
	 * Here we have a simplified code from tcp_addoptions(),
	 * without a proper loop, and having most of paddings hardcoded.
	 * We only consider fixed options that we would send every
	 * time I.e. SACK is not considered.
	 * 
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