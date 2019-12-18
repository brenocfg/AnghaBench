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
struct smbioc_t2rq {int ioc_setupcnt; int ioc_rparamcnt; int ioc_rdatacnt; int /*<<< orphan*/  ioc_rdata; int /*<<< orphan*/  ioc_rparam; int /*<<< orphan*/  ioc_tdata; int /*<<< orphan*/  ioc_tdatacnt; int /*<<< orphan*/  ioc_tparam; int /*<<< orphan*/  ioc_tparamcnt; scalar_t__ ioc_name; int /*<<< orphan*/ * ioc_setup; } ;
struct mdchain {scalar_t__ md_top; } ;
struct smb_t2rq {int t2_setupcount; int t2_maxpcount; int t2_maxdcount; int /*<<< orphan*/ * t_name; struct mdchain t2_rdata; struct mdchain t2_rparam; int /*<<< orphan*/  t2_tdata; int /*<<< orphan*/  t2_tparam; scalar_t__ t2_maxscount; int /*<<< orphan*/ * t2_setupdata; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MB_MUSER ; 
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 int /*<<< orphan*/  free (struct smb_t2rq*,int /*<<< orphan*/ ) ; 
 int m_fixhdr (scalar_t__) ; 
 struct smb_t2rq* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int md_get_mem (struct mdchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smb_cpdatain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * smb_strdupin (scalar_t__,int) ; 
 int /*<<< orphan*/  smb_strfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_t2_done (struct smb_t2rq*) ; 
 int smb_t2_init (struct smb_t2rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*) ; 
 int smb_t2_request (struct smb_t2rq*) ; 

int
smb_usr_t2request(struct smb_share *ssp, struct smbioc_t2rq *dp,
	struct smb_cred *scred)
{
	struct smb_t2rq *t2p;
	struct mdchain *mdp;
	int error, len;

	if (dp->ioc_setupcnt > 3)
		return EINVAL;
	t2p = malloc(sizeof(struct smb_t2rq), M_SMBTEMP, M_WAITOK);
	error = smb_t2_init(t2p, SSTOCP(ssp), dp->ioc_setup[0], scred);
	if (error) {
		free(t2p, M_SMBTEMP);
		return error;
	}
	len = t2p->t2_setupcount = dp->ioc_setupcnt;
	if (len > 1)
		t2p->t2_setupdata = dp->ioc_setup; 
	if (dp->ioc_name) {
		t2p->t_name = smb_strdupin(dp->ioc_name, 128);
		if (t2p->t_name == NULL) {
			error = ENOMEM;
			goto bad;
		}
	}
	t2p->t2_maxscount = 0;
	t2p->t2_maxpcount = dp->ioc_rparamcnt;
	t2p->t2_maxdcount = dp->ioc_rdatacnt;
	error = smb_cpdatain(&t2p->t2_tparam, dp->ioc_tparamcnt, dp->ioc_tparam);
	if (error)
		goto bad;
	error = smb_cpdatain(&t2p->t2_tdata, dp->ioc_tdatacnt, dp->ioc_tdata);
	if (error)
		goto bad;
	error = smb_t2_request(t2p);
	if (error)
		goto bad;
	mdp = &t2p->t2_rparam;
	if (mdp->md_top) {
		len = m_fixhdr(mdp->md_top);
		if (len > dp->ioc_rparamcnt) {
			error = EMSGSIZE;
			goto bad;
		}
		dp->ioc_rparamcnt = len;
		error = md_get_mem(mdp, dp->ioc_rparam, len, MB_MUSER);
		if (error)
			goto bad;
	} else
		dp->ioc_rparamcnt = 0;
	mdp = &t2p->t2_rdata;
	if (mdp->md_top) {
		len = m_fixhdr(mdp->md_top);
		if (len > dp->ioc_rdatacnt) {
			error = EMSGSIZE;
			goto bad;
		}
		dp->ioc_rdatacnt = len;
		error = md_get_mem(mdp, dp->ioc_rdata, len, MB_MUSER);
	} else
		dp->ioc_rdatacnt = 0;
bad:
	if (t2p->t_name)
		smb_strfree(t2p->t_name);
	smb_t2_done(t2p);
	free(t2p, M_SMBTEMP);
	return error;
}