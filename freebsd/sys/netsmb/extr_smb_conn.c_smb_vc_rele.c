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
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCTOCP (struct smb_vc*) ; 
 int /*<<< orphan*/  smb_co_rele (int /*<<< orphan*/ ,struct smb_cred*) ; 

void
smb_vc_rele(struct smb_vc *vcp, struct smb_cred *scred)
{
	smb_co_rele(VCTOCP(vcp), scred);
}