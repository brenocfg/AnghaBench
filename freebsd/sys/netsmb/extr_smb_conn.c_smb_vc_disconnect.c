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
struct smb_vc {int /*<<< orphan*/ * vc_iod; } ;

/* Variables and functions */
 int SMBIOD_EV_DISCONNECT ; 
 int SMBIOD_EV_SYNC ; 
 int /*<<< orphan*/  smb_iod_request (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
smb_vc_disconnect(struct smb_vc *vcp)
{

	if (vcp->vc_iod != NULL)
		smb_iod_request(vcp->vc_iod, SMBIOD_EV_DISCONNECT |
		    SMBIOD_EV_SYNC, NULL);
	return 0;
}