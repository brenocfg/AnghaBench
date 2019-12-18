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
struct smbiod {struct thread* iod_td; struct smb_vc* iod_vc; } ;
struct smb_vc {int /*<<< orphan*/ * vc_tdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_TRAN_DISCONNECT (struct smb_vc*,struct thread*) ; 
 int /*<<< orphan*/  SMB_TRAN_DONE (struct smb_vc*,struct thread*) ; 

__attribute__((used)) static void
smb_iod_closetran(struct smbiod *iod)
{
	struct smb_vc *vcp = iod->iod_vc;
	struct thread *td = iod->iod_td;

	if (vcp->vc_tdata == NULL)
		return;
	SMB_TRAN_DISCONNECT(vcp, td);
	SMB_TRAN_DONE(vcp, td);
	vcp->vc_tdata = NULL;
}