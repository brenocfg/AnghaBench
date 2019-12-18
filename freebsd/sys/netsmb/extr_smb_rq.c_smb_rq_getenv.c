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
struct smb_vc {int vc_srvname; } ;
struct smb_share {int ss_name; } ;
struct smb_connobj {int co_level; struct smb_connobj* co_parent; } ;

/* Variables and functions */
 struct smb_share* CPTOSS (struct smb_connobj*) ; 
 struct smb_vc* CPTOVC (struct smb_connobj*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SMBERROR (char*,int) ; 
#define  SMBL_SHARE 129 
#define  SMBL_VC 128 

__attribute__((used)) static int
smb_rq_getenv(struct smb_connobj *layer,
	struct smb_vc **vcpp, struct smb_share **sspp)
{
	struct smb_vc *vcp = NULL;
	struct smb_share *ssp = NULL;
	struct smb_connobj *cp;
	int error = 0;

	switch (layer->co_level) {
	    case SMBL_VC:
		vcp = CPTOVC(layer);
		if (layer->co_parent == NULL) {
			SMBERROR("zombie VC %s\n", vcp->vc_srvname);
			error = EINVAL;
			break;
		}
		break;
	    case SMBL_SHARE:
		ssp = CPTOSS(layer);
		cp = layer->co_parent;
		if (cp == NULL) {
			SMBERROR("zombie share %s\n", ssp->ss_name);
			error = EINVAL;
			break;
		}
		error = smb_rq_getenv(cp, &vcp, NULL);
		if (error)
			break;
		break;
	    default:
		SMBERROR("invalid layer %d passed\n", layer->co_level);
		error = EINVAL;
	}
	if (vcpp)
		*vcpp = vcp;
	if (sspp)
		*sspp = ssp;
	return error;
}