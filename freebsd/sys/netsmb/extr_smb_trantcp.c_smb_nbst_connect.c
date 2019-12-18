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
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct thread {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr_nb {struct sockaddr_in snb_addrin; } ;
struct sockaddr {int sa_len; } ;
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {struct timespec nbp_timo; struct sockaddr_nb* nbp_paddr; int /*<<< orphan*/ * nbp_laddr; int /*<<< orphan*/ * nbp_tso; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NBDEBUG (char*) ; 
 int NB_MINSALEN ; 
 int /*<<< orphan*/  free (struct sockaddr_nb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int nb_connect_in (struct nbpcb*,struct sockaddr_in*,struct thread*) ; 
 int nbssn_rq_request (struct nbpcb*,struct thread*) ; 
 int /*<<< orphan*/  smb_nbst_disconnect (struct smb_vc*,struct thread*) ; 
 scalar_t__ sodupsockaddr (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static int
smb_nbst_connect(struct smb_vc *vcp, struct sockaddr *sap, struct thread *td)
{
	struct nbpcb *nbp = vcp->vc_tdata;
	struct sockaddr_in sin;
	struct sockaddr_nb *snb;
	struct timespec ts1, ts2;
	int error, slen;

	NBDEBUG("\n");
	if (nbp->nbp_tso != NULL)
		return EISCONN;
	if (nbp->nbp_laddr == NULL)
		return EINVAL;
	slen = sap->sa_len;
	if (slen < NB_MINSALEN)
		return EINVAL;
	if (nbp->nbp_paddr) {
		free(nbp->nbp_paddr, M_SONAME);
		nbp->nbp_paddr = NULL;
	}
	snb = (struct sockaddr_nb*)sodupsockaddr(sap, M_WAITOK);
	if (snb == NULL)
		return ENOMEM;
	nbp->nbp_paddr = snb;
	sin = snb->snb_addrin;
	getnanotime(&ts1);
	error = nb_connect_in(nbp, &sin, td);
	if (error)
		return error;
	getnanotime(&ts2);
	timespecsub(&ts2, &ts1, &ts2);
	if (ts2.tv_sec == 0) {
		ts2.tv_sec = 1;
		ts2.tv_nsec = 0;
	}
	timespecadd(&ts2, &ts2, &nbp->nbp_timo);
	timespecadd(&nbp->nbp_timo, &ts2, &nbp->nbp_timo);
	timespecadd(&nbp->nbp_timo, &ts2, &nbp->nbp_timo);	/*  * 4 */
	error = nbssn_rq_request(nbp, td);
	if (error)
		smb_nbst_disconnect(vcp, td);
	return error;
}