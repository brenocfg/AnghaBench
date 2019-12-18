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
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {scalar_t__ nbp_state; struct socket* nbp_tso; int /*<<< orphan*/  nbp_flags; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  NBF_CONNECTED ; 
 scalar_t__ NBST_CLOSED ; 
 scalar_t__ NBST_RETARGET ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  soshutdown (struct socket*,int) ; 

__attribute__((used)) static int
smb_nbst_disconnect(struct smb_vc *vcp, struct thread *td)
{
	struct nbpcb *nbp = vcp->vc_tdata;
	struct socket *so;

	if (nbp == NULL || nbp->nbp_tso == NULL)
		return ENOTCONN;
	if ((so = nbp->nbp_tso) != NULL) {
		nbp->nbp_flags &= ~NBF_CONNECTED;
		nbp->nbp_tso = (struct socket *)NULL;
		soshutdown(so, 2);
		soclose(so);
	}
	if (nbp->nbp_state != NBST_RETARGET) {
		nbp->nbp_state = NBST_CLOSED;
	}
	return 0;
}