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
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {scalar_t__ nbp_state; int /*<<< orphan*/  nbp_tso; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  M_PREPEND (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ NBST_SESSION ; 
 int /*<<< orphan*/  NB_SSN_MESSAGE ; 
 scalar_t__ m_fixhdr (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nb_sethdr (struct mbuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int nb_sosend (int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
smb_nbst_send(struct smb_vc *vcp, struct mbuf *m0, struct thread *td)
{
	struct nbpcb *nbp = vcp->vc_tdata;
	int error;

	if (nbp->nbp_state != NBST_SESSION) {
		error = ENOTCONN;
		goto abort;
	}
	M_PREPEND(m0, 4, M_WAITOK);
	nb_sethdr(m0, NB_SSN_MESSAGE, m_fixhdr(m0) - 4);
	error = nb_sosend(nbp->nbp_tso, m0, 0, td);
	return error;
abort:
	if (m0)
		m_freem(m0);
	return error;
}