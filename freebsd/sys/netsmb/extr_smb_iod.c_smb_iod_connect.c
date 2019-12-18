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
struct smbiod {int iod_state; int /*<<< orphan*/  iod_scred; int /*<<< orphan*/  iod_flags; struct thread* iod_td; struct smb_vc* iod_vc; } ;
struct smb_vc {int /*<<< orphan*/  vc_paddr; scalar_t__ vc_laddr; int /*<<< orphan*/  vc_genid; } ;

/* Variables and functions */
 int EISCONN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  SMBERROR (char*) ; 
 int /*<<< orphan*/  SMBIODEBUG (char*,...) ; 
#define  SMBIOD_ST_DEAD 129 
 int SMBIOD_ST_TRANACTIVE ; 
#define  SMBIOD_ST_VCACTIVE 128 
 int /*<<< orphan*/  SMBTP_SELECTID ; 
 scalar_t__ SMB_TRAN_BIND (struct smb_vc*,scalar_t__,struct thread*) ; 
 scalar_t__ SMB_TRAN_CONNECT (struct smb_vc*,int /*<<< orphan*/ ,struct thread*) ; 
 scalar_t__ SMB_TRAN_CREATE (struct smb_vc*,struct thread*) ; 
 int /*<<< orphan*/  SMB_TRAN_SETPARAM (struct smb_vc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_iod_dead (struct smbiod*) ; 
 int /*<<< orphan*/  smb_iod_invrq (struct smbiod*) ; 
 scalar_t__ smb_smb_negotiate (struct smb_vc*,int /*<<< orphan*/ *) ; 
 scalar_t__ smb_smb_ssnsetup (struct smb_vc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb_iod_connect(struct smbiod *iod)
{
	struct smb_vc *vcp = iod->iod_vc;
	struct thread *td = iod->iod_td;
	int error;

	SMBIODEBUG("%d\n", iod->iod_state);
	switch(iod->iod_state) {
	    case SMBIOD_ST_VCACTIVE:
		SMBERROR("called for already opened connection\n");
		return EISCONN;
	    case SMBIOD_ST_DEAD:
		return ENOTCONN;	/* XXX: last error code ? */
	    default:
		break;
	}
	vcp->vc_genid++;
	error = 0;

	error = (int)SMB_TRAN_CREATE(vcp, td);
	if (error)
		goto fail;
	SMBIODEBUG("tcreate\n");
	if (vcp->vc_laddr) {
		error = (int)SMB_TRAN_BIND(vcp, vcp->vc_laddr, td);
		if (error)
			goto fail;
	}
	SMBIODEBUG("tbind\n");
	error = (int)SMB_TRAN_CONNECT(vcp, vcp->vc_paddr, td);
	if (error)
		goto fail;
	SMB_TRAN_SETPARAM(vcp, SMBTP_SELECTID, &iod->iod_flags);
	iod->iod_state = SMBIOD_ST_TRANACTIVE;
	SMBIODEBUG("tconnect\n");
	/* vcp->vc_mid = 0;*/
	error = (int)smb_smb_negotiate(vcp, &iod->iod_scred);
	if (error)
		goto fail;
	SMBIODEBUG("snegotiate\n");
	error = (int)smb_smb_ssnsetup(vcp, &iod->iod_scred);
	if (error)
		goto fail;
	iod->iod_state = SMBIOD_ST_VCACTIVE;
	SMBIODEBUG("completed\n");
	smb_iod_invrq(iod);
	return (0);

 fail:
	smb_iod_dead(iod);
	return (error);
}