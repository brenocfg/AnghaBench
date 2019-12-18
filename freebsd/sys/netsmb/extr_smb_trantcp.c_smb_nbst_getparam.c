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
struct timespec {int dummy; } ;
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {int nbp_sndbuf; int nbp_rcvbuf; struct timespec nbp_timo; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SMBTP_RCVSZ 130 
#define  SMBTP_SNDSZ 129 
#define  SMBTP_TIMEOUT 128 

__attribute__((used)) static int
smb_nbst_getparam(struct smb_vc *vcp, int param, void *data)
{
	struct nbpcb *nbp = vcp->vc_tdata;

	switch (param) {
	    case SMBTP_SNDSZ:
		*(int*)data = nbp->nbp_sndbuf;
		break;
	    case SMBTP_RCVSZ:
		*(int*)data = nbp->nbp_rcvbuf;
		break;
	    case SMBTP_TIMEOUT:
		*(struct timespec*)data = nbp->nbp_timo;
		break;
	    default:
		return EINVAL;
	}
	return 0;
}