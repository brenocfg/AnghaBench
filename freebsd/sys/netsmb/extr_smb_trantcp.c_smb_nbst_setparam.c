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
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {void* nbp_selectid; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SMBTP_SELECTID 128 

__attribute__((used)) static int
smb_nbst_setparam(struct smb_vc *vcp, int param, void *data)
{
	struct nbpcb *nbp = vcp->vc_tdata;

	switch (param) {
	    case SMBTP_SELECTID:
		nbp->nbp_selectid = data;
		break;
	    default:
		return EINVAL;
	}
	return 0;
}