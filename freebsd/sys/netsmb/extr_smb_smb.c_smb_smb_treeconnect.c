#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int co_flags; } ;
struct TYPE_3__ {int sv_sm; } ;
struct smb_vc {int vc_hflags2; char* vc_srvname; int /*<<< orphan*/  vc_ucs_tolocal; int /*<<< orphan*/  vc_tolocal; int /*<<< orphan*/  vc_ucs_toserver; int /*<<< orphan*/  vc_toserver; TYPE_2__ obj; int /*<<< orphan*/  vc_genid; int /*<<< orphan*/  vc_ch; TYPE_1__ vc_sopt; int /*<<< orphan*/  vc_toupper; int /*<<< orphan*/  vc_cp_tolocal; int /*<<< orphan*/  vc_cp_toserver; } ;
struct smb_share {char* ss_name; int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_vcgenid; int /*<<< orphan*/  ss_tid; int /*<<< orphan*/  ss_type; } ;
struct mbchain {int dummy; } ;
struct smb_rq {int /*<<< orphan*/  sr_rptid; struct mbchain sr_rq; struct smb_vc* sr_vc; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBSDEBUG (char*,int) ; 
 int /*<<< orphan*/  SMBS_CONNECTED ; 
 int SMBV_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_TREE_CONNECT_ANDX ; 
 int SMB_CS_NONE ; 
 int SMB_FLAGS2_UNICODE ; 
 int SMB_MAXPASSWORDLEN ; 
 int SMB_SM_ENCRYPT ; 
 int SMB_SM_USER ; 
 int /*<<< orphan*/  SMB_TID_UNKNOWN ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 struct smb_vc* SSTOVC (struct smb_share*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iconv_convstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int) ; 
 int /*<<< orphan*/  smb_encrypt (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smb_put_dmem (struct mbchain*,struct smb_vc*,char*,int,int) ; 
 int /*<<< orphan*/  smb_put_dstring (struct mbchain*,struct smb_vc*,char*,int) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_share_getpass (struct smb_share*) ; 
 char* smb_share_typename (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int
smb_smb_treeconnect(struct smb_share *ssp, struct smb_cred *scred)
{
	struct smb_vc *vcp;
	struct smb_rq rq, *rqp = &rq;
	struct mbchain *mbp;
	char *pp, *pbuf, *encpass;
	int error, plen, caseopt, upper;

	upper = 0;

again:
	/* Disable Unicode for SMB_COM_TREE_CONNECT_ANDX requests */
	if (SSTOVC(ssp)->vc_hflags2 & SMB_FLAGS2_UNICODE) {
		vcp = SSTOVC(ssp);
		vcp->vc_toserver = vcp->vc_cp_toserver;
		vcp->vc_tolocal = vcp->vc_cp_tolocal;
		vcp->vc_hflags2 &= ~SMB_FLAGS2_UNICODE;
	}

	ssp->ss_tid = SMB_TID_UNKNOWN;
	error = smb_rq_alloc(SSTOCP(ssp), SMB_COM_TREE_CONNECT_ANDX, scred, &rqp);
	if (error)
		return error;
	vcp = rqp->sr_vc;
	caseopt = SMB_CS_NONE;
	if (vcp->vc_sopt.sv_sm & SMB_SM_USER) {
		plen = 1;
		pp = "";
		pbuf = NULL;
		encpass = NULL;
	} else {
		pbuf = malloc(SMB_MAXPASSWORDLEN + 1, M_SMBTEMP, M_WAITOK);
		encpass = malloc(24, M_SMBTEMP, M_WAITOK);
		/*
		 * We try w/o uppercasing first so Samba mixed case
		 * passwords work.  If that fails we come back and try
		 * uppercasing to satisfy OS/2 and Windows for Workgroups.
		 */
		if (upper++) {
			iconv_convstr(vcp->vc_toupper, pbuf,
				      smb_share_getpass(ssp)/*,
				      SMB_MAXPASSWORDLEN*/);
		} else {
			strncpy(pbuf, smb_share_getpass(ssp),
				SMB_MAXPASSWORDLEN);
			pbuf[SMB_MAXPASSWORDLEN] = '\0';
		}
		if (vcp->vc_sopt.sv_sm & SMB_SM_ENCRYPT) {
			plen = 24;
			smb_encrypt(pbuf, vcp->vc_ch, encpass);
			pp = encpass;
		} else {
			plen = strlen(pbuf) + 1;
			pp = pbuf;
		}
	}
	mbp = &rqp->sr_rq;
	smb_rq_wstart(rqp);
	mb_put_uint8(mbp, 0xff);
	mb_put_uint8(mbp, 0);
	mb_put_uint16le(mbp, 0);
	mb_put_uint16le(mbp, 0);		/* Flags */
	mb_put_uint16le(mbp, plen);
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	mb_put_mem(mbp, pp, plen, MB_MSYSTEM);
	smb_put_dmem(mbp, vcp, "\\\\", 2, caseopt);
	pp = vcp->vc_srvname;
	smb_put_dmem(mbp, vcp, pp, strlen(pp), caseopt);
	smb_put_dmem(mbp, vcp, "\\", 1, caseopt);
	pp = ssp->ss_name;
	smb_put_dstring(mbp, vcp, pp, caseopt);
	pp = smb_share_typename(ssp->ss_type);
	smb_put_dstring(mbp, vcp, pp, caseopt);
	smb_rq_bend(rqp);
	error = smb_rq_simple(rqp);
	SMBSDEBUG("%d\n", error);
	if (error)
		goto bad;
	ssp->ss_tid = rqp->sr_rptid;
	ssp->ss_vcgenid = vcp->vc_genid;
	ssp->ss_flags |= SMBS_CONNECTED;
	/*
	 * If the server can speak Unicode then switch
	 * our converters to do Unicode <--> Local
	 */
	if (vcp->obj.co_flags & SMBV_UNICODE) {
		vcp->vc_toserver = vcp->vc_ucs_toserver;
		vcp->vc_tolocal = vcp->vc_ucs_tolocal;
		vcp->vc_hflags2 |= SMB_FLAGS2_UNICODE;
	}
bad:
	if (encpass)
		free(encpass, M_SMBTEMP);
	if (pbuf)
		free(pbuf, M_SMBTEMP);
	smb_rq_done(rqp);
	if (error && upper == 1)
		goto again;
	return error;
}