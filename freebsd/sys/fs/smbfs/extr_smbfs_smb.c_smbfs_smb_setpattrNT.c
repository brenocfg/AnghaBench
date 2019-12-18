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
typedef  int /*<<< orphan*/  u_short ;
struct timespec {int dummy; } ;
struct smbnode {TYPE_1__* n_mount; } ;
struct TYPE_4__ {int sv_tz; } ;
struct smb_vc {TYPE_2__ vc_sopt; } ;
struct mbchain {int dummy; } ;
struct smb_t2rq {int t2_maxpcount; int t2_maxdcount; struct mbchain t2_tdata; struct mbchain t2_tparam; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {struct smb_share* sm_share; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_SET_FILE_BASIC_INFO ; 
 int /*<<< orphan*/  SMB_TRANS2_SET_PATH_INFORMATION ; 
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 struct smb_vc* SSTOVC (struct smb_share*) ; 
 int /*<<< orphan*/  mb_init (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_int64le (struct mbchain*,scalar_t__) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int smb_t2_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_t2rq**) ; 
 int /*<<< orphan*/  smb_t2_done (struct smb_t2rq*) ; 
 int smb_t2_request (struct smb_t2rq*) ; 
 int /*<<< orphan*/  smb_time_local2NT (struct timespec*,int,scalar_t__*) ; 
 int smbfs_fullpath (struct mbchain*,struct smb_vc*,struct smbnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
smbfs_smb_setpattrNT(struct smbnode *np, u_short attr, struct timespec *mtime,
	struct timespec *atime, struct smb_cred *scred)
{
	struct smb_t2rq *t2p;
	struct smb_share *ssp = np->n_mount->sm_share;
	struct smb_vc *vcp = SSTOVC(ssp);
	struct mbchain *mbp;
	int64_t tm;
	int error, tzoff;

	error = smb_t2_alloc(SSTOCP(ssp), SMB_TRANS2_SET_PATH_INFORMATION,
	    scred, &t2p);
	if (error)
		return error;
	mbp = &t2p->t2_tparam;
	mb_init(mbp);
	mb_put_uint16le(mbp, SMB_SET_FILE_BASIC_INFO);
	mb_put_uint32le(mbp, 0);		/* MBZ */
	/* mb_put_uint8(mbp, SMB_DT_ASCII); specs incorrect */
	error = smbfs_fullpath(mbp, vcp, np, NULL, 0);
	if (error) {
		smb_t2_done(t2p);
		return error;
	}
	tzoff = vcp->vc_sopt.sv_tz;
	mbp = &t2p->t2_tdata;
	mb_init(mbp);
	mb_put_int64le(mbp, 0);		/* creation time */
	if (atime) {
		smb_time_local2NT(atime, tzoff, &tm);
	} else
		tm = 0;
	mb_put_int64le(mbp, tm);
	if (mtime) {
		smb_time_local2NT(mtime, tzoff, &tm);
	} else
		tm = 0;
	mb_put_int64le(mbp, tm);
	mb_put_int64le(mbp, tm);		/* change time */
	mb_put_uint32le(mbp, attr);		/* attr */
	t2p->t2_maxpcount = 24;
	t2p->t2_maxdcount = 56;
	error = smb_t2_request(t2p);
	smb_t2_done(t2p);
	return error;
}