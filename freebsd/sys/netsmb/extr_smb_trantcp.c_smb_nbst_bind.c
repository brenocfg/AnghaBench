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
struct sockaddr_nb {int dummy; } ;
struct sockaddr {int sa_len; } ;
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {int nbp_flags; struct sockaddr_nb* nbp_laddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NBDEBUG (char*) ; 
 int NBF_LOCADDR ; 
 int NB_MINSALEN ; 
 scalar_t__ sodupsockaddr (struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_nbst_bind(struct smb_vc *vcp, struct sockaddr *sap, struct thread *td)
{
	struct nbpcb *nbp = vcp->vc_tdata;
	struct sockaddr_nb *snb;
	int error, slen;

	NBDEBUG("\n");
	error = EINVAL;
	do {
		if (nbp->nbp_flags & NBF_LOCADDR)
			break;
		/*
		 * It is possible to create NETBIOS name in the kernel,
		 * but nothing prevents us to do it in the user space.
		 */
		if (sap == NULL)
			break;
		slen = sap->sa_len;
		if (slen < NB_MINSALEN)
			break;
		snb = (struct sockaddr_nb*)sodupsockaddr(sap, M_WAITOK);
		if (snb == NULL) {
			error = ENOMEM;
			break;
		}
		nbp->nbp_laddr = snb;
		nbp->nbp_flags |= NBF_LOCADDR;
		error = 0;
	} while(0);
	return error;
}