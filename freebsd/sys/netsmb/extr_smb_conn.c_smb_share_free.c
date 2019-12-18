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
struct smb_share {int /*<<< orphan*/  ss_stlock; int /*<<< orphan*/  ss_pass; int /*<<< orphan*/  ss_name; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 struct smb_share* CPTOSS (struct smb_connobj*) ; 
 int /*<<< orphan*/  M_SMBCONN ; 
 int /*<<< orphan*/  SMB_STRFREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 int /*<<< orphan*/  free (struct smb_share*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_co_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_sl_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb_share_free(struct smb_connobj *cp)
{
	struct smb_share *ssp = CPTOSS(cp);

	SMB_STRFREE(ssp->ss_name);
	SMB_STRFREE(ssp->ss_pass);
	smb_sl_destroy(&ssp->ss_stlock);
	smb_co_done(SSTOCP(ssp));
	free(ssp, M_SMBCONN);
}