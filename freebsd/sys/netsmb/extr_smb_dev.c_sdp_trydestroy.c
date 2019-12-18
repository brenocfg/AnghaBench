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
struct smb_vc {int dummy; } ;
struct smb_share {int dummy; } ;
struct smb_dev {scalar_t__ refcount; struct smb_vc* sd_vc; struct smb_share* sd_share; } ;
struct smb_cred {scalar_t__ refcount; struct smb_vc* sd_vc; struct smb_share* sd_share; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_NSMBDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMB_LOCKASSERT () ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct smb_dev*,int /*<<< orphan*/ ) ; 
 struct smb_dev* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_share_lock (struct smb_share*) ; 
 int /*<<< orphan*/  smb_share_rele (struct smb_share*,struct smb_dev*) ; 
 int /*<<< orphan*/  smb_vc_lock (struct smb_vc*) ; 
 int /*<<< orphan*/  smb_vc_rele (struct smb_vc*,struct smb_dev*) ; 

void
sdp_trydestroy(struct smb_dev *sdp)
{
	struct smb_vc *vcp;
	struct smb_share *ssp;
	struct smb_cred *scred;

	SMB_LOCKASSERT();
	if (!sdp)
		panic("No smb_dev upon device close");
	MPASS(sdp->refcount > 0);
	sdp->refcount--;
	if (sdp->refcount) 
		return;
	scred = malloc(sizeof(struct smb_cred), M_NSMBDEV, M_WAITOK);
	smb_makescred(scred, curthread, NULL);
	ssp = sdp->sd_share;
	if (ssp != NULL) {
		smb_share_lock(ssp);
		smb_share_rele(ssp, scred);
	}
	vcp = sdp->sd_vc;
	if (vcp != NULL) {
		smb_vc_lock(vcp);
		smb_vc_rele(vcp, scred);
	}
	free(scred, M_NSMBDEV);
	free(sdp, M_NSMBDEV);
	return;
}