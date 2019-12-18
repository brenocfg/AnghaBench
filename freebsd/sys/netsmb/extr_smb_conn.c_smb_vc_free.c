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
struct smb_vc {int /*<<< orphan*/  vc_stlock; scalar_t__ vc_ucs_toserver; scalar_t__ vc_ucs_tolocal; scalar_t__ vc_cp_toserver; scalar_t__ vc_cp_tolocal; int /*<<< orphan*/ * vc_toserver; int /*<<< orphan*/ * vc_tolocal; scalar_t__ vc_toupper; scalar_t__ vc_tolower; struct smb_vc* vc_laddr; struct smb_vc* vc_paddr; struct smb_vc* vc_mackey; int /*<<< orphan*/  vc_domain; int /*<<< orphan*/  vc_pass; int /*<<< orphan*/  vc_srvname; int /*<<< orphan*/  vc_username; scalar_t__ vc_iod; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 struct smb_vc* CPTOVC (struct smb_connobj*) ; 
 int /*<<< orphan*/  M_SMBCONN ; 
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SMB_STRFREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCTOCP (struct smb_vc*) ; 
 int /*<<< orphan*/  free (struct smb_vc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 int /*<<< orphan*/  smb_co_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_iod_destroy (scalar_t__) ; 
 int /*<<< orphan*/  smb_sl_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb_vc_free(struct smb_connobj *cp)
{
	struct smb_vc *vcp = CPTOVC(cp);

	if (vcp->vc_iod)
		smb_iod_destroy(vcp->vc_iod);
	SMB_STRFREE(vcp->vc_username);
	SMB_STRFREE(vcp->vc_srvname);
	SMB_STRFREE(vcp->vc_pass);
	SMB_STRFREE(vcp->vc_domain);
	if (vcp->vc_mackey)
		free(vcp->vc_mackey, M_SMBTEMP);
	if (vcp->vc_paddr)
		free(vcp->vc_paddr, M_SONAME);
	if (vcp->vc_laddr)
		free(vcp->vc_laddr, M_SONAME);
	if (vcp->vc_tolower)
		iconv_close(vcp->vc_tolower);
	if (vcp->vc_toupper)
		iconv_close(vcp->vc_toupper);
	if (vcp->vc_tolocal)
		vcp->vc_tolocal = NULL;
	if (vcp->vc_toserver)
		vcp->vc_toserver = NULL;
	if (vcp->vc_cp_tolocal)
		iconv_close(vcp->vc_cp_tolocal);
	if (vcp->vc_cp_toserver)
		iconv_close(vcp->vc_cp_toserver);
	if (vcp->vc_ucs_tolocal)
		iconv_close(vcp->vc_ucs_tolocal);
	if (vcp->vc_ucs_toserver)
		iconv_close(vcp->vc_ucs_toserver);
	smb_co_done(VCTOCP(vcp));
	smb_sl_destroy(&vcp->vc_stlock);
	free(vcp, M_SMBCONN);
}