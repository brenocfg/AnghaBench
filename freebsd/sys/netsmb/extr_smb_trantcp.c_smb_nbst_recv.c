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
typedef  int /*<<< orphan*/  u_int8_t ;
struct thread {int dummy; } ;
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {int /*<<< orphan*/  nbp_flags; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBF_RECVLOCK ; 
 int nbssn_recv (struct nbpcb*,struct mbuf**,int*,int /*<<< orphan*/ *,struct thread*) ; 

__attribute__((used)) static int
smb_nbst_recv(struct smb_vc *vcp, struct mbuf **mpp, struct thread *td)
{
	struct nbpcb *nbp = vcp->vc_tdata;
	u_int8_t rpcode;
	int error, rplen;

	nbp->nbp_flags |= NBF_RECVLOCK;
	error = nbssn_recv(nbp, mpp, &rplen, &rpcode, td);
	nbp->nbp_flags &= ~NBF_RECVLOCK;
	return error;
}