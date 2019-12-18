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
struct smb_vc {int /*<<< orphan*/  vc_iod; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int SMBIOD_EV_CONNECT ; 
 int SMBIOD_EV_SYNC ; 
 int smb_iod_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
smb_vc_connect(struct smb_vc *vcp, struct smb_cred *scred)
{

	return smb_iod_request(vcp->vc_iod, SMBIOD_EV_CONNECT | SMBIOD_EV_SYNC, NULL);
}