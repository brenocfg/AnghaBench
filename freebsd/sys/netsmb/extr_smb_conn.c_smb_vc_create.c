#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct ucred {scalar_t__ cr_uid; scalar_t__* cr_groups; } ;
struct smb_vcspec {scalar_t__ owner; scalar_t__ group; char* domain; int rights; int flags; char* pass; char* srvname; char* username; char* localcs; char* servercs; int /*<<< orphan*/  lap; int /*<<< orphan*/  sap; } ;
struct TYPE_2__ {int co_flags; int /*<<< orphan*/  co_gone; int /*<<< orphan*/  co_free; } ;
struct smb_vc {int vc_mode; int /*<<< orphan*/ * vc_ucs_tolocal; int /*<<< orphan*/ * vc_ucs_toserver; int /*<<< orphan*/ * vc_cp_tolocal; int /*<<< orphan*/ * vc_tolocal; int /*<<< orphan*/ * vc_cp_toserver; int /*<<< orphan*/ * vc_toserver; int /*<<< orphan*/ * vc_toupper; int /*<<< orphan*/ * vc_tolower; int /*<<< orphan*/ * vc_username; int /*<<< orphan*/ * vc_srvname; int /*<<< orphan*/ * vc_domain; int /*<<< orphan*/ * vc_pass; int /*<<< orphan*/ * vc_laddr; int /*<<< orphan*/ * vc_paddr; int /*<<< orphan*/  vc_stlock; scalar_t__ vc_grp; scalar_t__ vc_uid; scalar_t__ vc_mackeylen; int /*<<< orphan*/ * vc_mackey; scalar_t__ vc_seqno; int /*<<< orphan*/ * vc_tdesc; TYPE_1__ obj; int /*<<< orphan*/  vc_smbuid; int /*<<< orphan*/  vc_timo; scalar_t__ vc_number; } ;
struct smb_cred {struct ucred* scr_cred; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 char* ENCODING_UNICODE ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  M_SMBCONN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBL_VC ; 
 scalar_t__ SMBM_ANY_GROUP ; 
 scalar_t__ SMBM_ANY_OWNER ; 
 int SMBM_MASK ; 
 int SMBV_PRIVATE ; 
 int SMBV_SINGLESHARE ; 
 int /*<<< orphan*/  SMB_DEFRQTIMO ; 
 int /*<<< orphan*/  SMB_UID_UNKNOWN ; 
 char* SMB_UNICODE_NAME ; 
 int /*<<< orphan*/  VCTOCP (struct smb_vc*) ; 
 int /*<<< orphan*/  groupmember (scalar_t__,struct ucred*) ; 
 int /*<<< orphan*/  iconv_add (char*,char*,char*) ; 
 int /*<<< orphan*/  iconv_close (int /*<<< orphan*/ *) ; 
 scalar_t__ iconv_open (char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  smb_co_addchild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_co_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ smb_iod_create (struct smb_vc*) ; 
 int /*<<< orphan*/  smb_sl_init (int /*<<< orphan*/ *,char*) ; 
 void* smb_strdup (char*) ; 
 scalar_t__ smb_suser (struct ucred*) ; 
 int /*<<< orphan*/  smb_tran_nbtcp_desc ; 
 int /*<<< orphan*/  smb_vc_free ; 
 int /*<<< orphan*/  smb_vc_gone ; 
 int /*<<< orphan*/  smb_vc_put (struct smb_vc*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_vclist ; 
 int /*<<< orphan*/  smb_vcnext ; 
 struct smb_vc* smb_zmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sodupsockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb_vc_create(struct smb_vcspec *vcspec,
	struct smb_cred *scred, struct smb_vc **vcpp)
{
	struct smb_vc *vcp;
	struct ucred *cred = scred->scr_cred;
	uid_t uid = vcspec->owner;
	gid_t gid = vcspec->group;
	uid_t realuid = cred->cr_uid;
	char *domain = vcspec->domain;
	int error, isroot;

	isroot = smb_suser(cred) == 0;
	/*
	 * Only superuser can create VCs with different uid and gid
	 */
	if (uid != SMBM_ANY_OWNER && uid != realuid && !isroot)
		return EPERM;
	if (gid != SMBM_ANY_GROUP && !groupmember(gid, cred) && !isroot)
		return EPERM;

	vcp = smb_zmalloc(sizeof(*vcp), M_SMBCONN, M_WAITOK);
	smb_co_init(VCTOCP(vcp), SMBL_VC, "smb_vc ilock", "smb_vc");
	vcp->obj.co_free = smb_vc_free;
	vcp->obj.co_gone = smb_vc_gone;
	vcp->vc_number = smb_vcnext++;
	vcp->vc_timo = SMB_DEFRQTIMO;
	vcp->vc_smbuid = SMB_UID_UNKNOWN;
	vcp->vc_mode = vcspec->rights & SMBM_MASK;
	vcp->obj.co_flags = vcspec->flags & (SMBV_PRIVATE | SMBV_SINGLESHARE);
	vcp->vc_tdesc = &smb_tran_nbtcp_desc;
	vcp->vc_seqno = 0;
	vcp->vc_mackey = NULL;
	vcp->vc_mackeylen = 0;

	if (uid == SMBM_ANY_OWNER)
		uid = realuid;
	if (gid == SMBM_ANY_GROUP)
		gid = cred->cr_groups[0];
	vcp->vc_uid = uid;
	vcp->vc_grp = gid;

	smb_sl_init(&vcp->vc_stlock, "vcstlock");
	error = ENOMEM;

	vcp->vc_paddr = sodupsockaddr(vcspec->sap, M_WAITOK);
	if (vcp->vc_paddr == NULL)
		goto fail;
	vcp->vc_laddr = sodupsockaddr(vcspec->lap, M_WAITOK);
	if (vcp->vc_laddr == NULL)
		goto fail;
	vcp->vc_pass = smb_strdup(vcspec->pass);
	if (vcp->vc_pass == NULL)
		goto fail;
	vcp->vc_domain = smb_strdup((domain && domain[0]) ? domain :
	    "NODOMAIN");
	if (vcp->vc_domain == NULL)
		goto fail;
	vcp->vc_srvname = smb_strdup(vcspec->srvname);
	if (vcp->vc_srvname == NULL)
		goto fail;
	vcp->vc_username = smb_strdup(vcspec->username);
	if (vcp->vc_username == NULL)
		goto fail;
	error = (int)iconv_open("tolower", vcspec->localcs, &vcp->vc_tolower);
	if (error)
		goto fail;
	error = (int)iconv_open("toupper", vcspec->localcs, &vcp->vc_toupper);
	if (error)
		goto fail;
	if (vcspec->servercs[0]) {
		error = (int)iconv_open(vcspec->servercs, vcspec->localcs,
		    &vcp->vc_cp_toserver);
		if (error)
			goto fail;
		error = (int)iconv_open(vcspec->localcs, vcspec->servercs,
		    &vcp->vc_cp_tolocal);
		if (error)
			goto fail;
		vcp->vc_toserver = vcp->vc_cp_toserver;
		vcp->vc_tolocal = vcp->vc_cp_tolocal;
		iconv_add(ENCODING_UNICODE, ENCODING_UNICODE, SMB_UNICODE_NAME);
		iconv_add(ENCODING_UNICODE, SMB_UNICODE_NAME, ENCODING_UNICODE);
		error = (int)iconv_open(SMB_UNICODE_NAME, vcspec->localcs,
		    &vcp->vc_ucs_toserver);
		if (!error) {
			error = (int)iconv_open(vcspec->localcs, SMB_UNICODE_NAME,
			    &vcp->vc_ucs_tolocal);
		}
		if (error) {
			if (vcp->vc_ucs_toserver)
				iconv_close(vcp->vc_ucs_toserver);
			vcp->vc_ucs_toserver = NULL;
			vcp->vc_ucs_tolocal = NULL;
		}
	}
	error = (int)smb_iod_create(vcp);
	if (error)
		goto fail;
	*vcpp = vcp;
	smb_co_addchild(&smb_vclist, VCTOCP(vcp));
	return (0);

 fail:
	smb_vc_put(vcp, scred);
	return (error);
}