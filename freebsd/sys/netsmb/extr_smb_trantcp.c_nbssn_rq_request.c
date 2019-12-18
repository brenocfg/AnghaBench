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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_int8_t ;
struct timeval {int dummy; } ;
struct thread {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct nbpcb {int /*<<< orphan*/  nbp_vc; int /*<<< orphan*/  nbp_state; int /*<<< orphan*/  nbp_flags; int /*<<< orphan*/  nbp_tso; int /*<<< orphan*/  nbp_timo; int /*<<< orphan*/  nbp_laddr; int /*<<< orphan*/  nbp_paddr; } ;
struct mdchain {int /*<<< orphan*/  mb_top; } ;
struct mbuf {int dummy; } ;
struct mbchain {int /*<<< orphan*/  mb_top; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ECONNABORTED ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  M_NBDATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NBDEBUG (char*,...) ; 
 int /*<<< orphan*/  NBF_CONNECTED ; 
 int /*<<< orphan*/  NBST_RETARGET ; 
 int /*<<< orphan*/  NBST_RQSENT ; 
 int /*<<< orphan*/  NBST_SESSION ; 
 scalar_t__ NB_SSN_POSRESP ; 
 int /*<<< orphan*/  NB_SSN_REQUEST ; 
 scalar_t__ NB_SSN_RTGRESP ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mdchain*,int /*<<< orphan*/ ) ; 
 struct mdchain* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_detach (struct mdchain*) ; 
 int /*<<< orphan*/  mb_done (struct mdchain*) ; 
 scalar_t__ mb_fixhdr (struct mdchain*) ; 
 int mb_init (struct mdchain*) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mdchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_done (struct mdchain*) ; 
 int /*<<< orphan*/  md_get_mem (struct mdchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_get_uint16 (struct mdchain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_initm (struct mdchain*,struct mbuf*) ; 
 int nb_connect_in (struct nbpcb*,struct sockaddr_in*,struct thread*) ; 
 int /*<<< orphan*/  nb_put_name (struct mdchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_sethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int nb_sosend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int nbssn_recv (struct nbpcb*,struct mbuf**,int*,scalar_t__*,struct thread*) ; 
 int selsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,struct thread*) ; 
 int /*<<< orphan*/  smb_nbst_disconnect (int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
nbssn_rq_request(struct nbpcb *nbp, struct thread *td)
{
	struct mbchain *mbp;
	struct mdchain *mdp;
	struct mbuf *m0;
	struct timeval tv;
	struct sockaddr_in sin;
	u_short port;
	u_int8_t rpcode;
	int error, rplen;

	mbp = malloc(sizeof(struct mbchain), M_NBDATA, M_WAITOK);
	mdp = malloc(sizeof(struct mbchain), M_NBDATA, M_WAITOK);
	error = mb_init(mbp);
	if (error) {
		free(mbp, M_NBDATA);
		free(mdp, M_NBDATA);
		return error;
	}
	mb_put_uint32le(mbp, 0);
	nb_put_name(mbp, nbp->nbp_paddr);
	nb_put_name(mbp, nbp->nbp_laddr);
	nb_sethdr(mbp->mb_top, NB_SSN_REQUEST, mb_fixhdr(mbp) - 4);
	error = nb_sosend(nbp->nbp_tso, mbp->mb_top, 0, td);
	if (!error) {
		nbp->nbp_state = NBST_RQSENT;
	}
	mb_detach(mbp);
	mb_done(mbp);
	free(mbp, M_NBDATA);
	if (error) {
		free(mdp, M_NBDATA);
		return error;
	}
	TIMESPEC_TO_TIMEVAL(&tv, &nbp->nbp_timo);
	error = selsocket(nbp->nbp_tso, POLLIN, &tv, td);
	if (error == EWOULDBLOCK) {	/* Timeout */
		NBDEBUG("initial request timeout\n");
		free(mdp, M_NBDATA);
		return ETIMEDOUT;
	}
	if (error) {			/* restart or interrupt */
		free(mdp, M_NBDATA);
		return error;
	}
	error = nbssn_recv(nbp, &m0, &rplen, &rpcode, td);
	if (error) {
		NBDEBUG("recv() error %d\n", error);
		free(mdp, M_NBDATA);
		return error;
	}
	/*
	 * Process NETBIOS reply
	 */
	if (m0)
		md_initm(mdp, m0);
	error = 0;
	do {
		if (rpcode == NB_SSN_POSRESP) {
			nbp->nbp_state = NBST_SESSION;
			nbp->nbp_flags |= NBF_CONNECTED;
			break;
		}
		if (rpcode != NB_SSN_RTGRESP) {
			error = ECONNABORTED;
			break;
		}
		if (rplen != 6) {
			error = ECONNABORTED;
			break;
		}
		md_get_mem(mdp, (caddr_t)&sin.sin_addr, 4, MB_MSYSTEM);
		md_get_uint16(mdp, &port);
		sin.sin_port = port;
		nbp->nbp_state = NBST_RETARGET;
		smb_nbst_disconnect(nbp->nbp_vc, td);
		error = nb_connect_in(nbp, &sin, td);
		if (!error)
			error = nbssn_rq_request(nbp, td);
		if (error) {
			smb_nbst_disconnect(nbp->nbp_vc, td);
			break;
		}
	} while(0);
	if (m0)
		md_done(mdp);
	free(mdp, M_NBDATA);
	return error;
}