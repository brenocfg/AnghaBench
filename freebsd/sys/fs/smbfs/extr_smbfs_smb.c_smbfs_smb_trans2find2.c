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
typedef  int u_int16_t ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct smbfs_fctx {int f_flags; int f_attrmask; int f_limit; int f_infolevel; int f_rnamelen; int f_ecnt; int f_rnameofs; scalar_t__ f_eofs; int /*<<< orphan*/  f_Sid; scalar_t__ f_rname; struct smb_t2rq* f_t2; int /*<<< orphan*/  f_scred; int /*<<< orphan*/  f_ssp; int /*<<< orphan*/  f_wclen; int /*<<< orphan*/  f_wildcard; int /*<<< orphan*/  f_dnp; } ;
struct smb_vc {int vc_flags; int /*<<< orphan*/  vc_txmax; } ;
struct mdchain {TYPE_1__* md_top; } ;
struct mbchain {TYPE_2__* mb_top; } ;
struct smb_t2rq {int t2_maxpcount; struct mdchain t2_rdata; struct mdchain t2_rparam; int /*<<< orphan*/  t2_maxdcount; struct mbchain t2_tparam; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  m_next; } ;
struct TYPE_3__ {scalar_t__ m_len; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int SMBC_WIN95 ; 
 int SMBFS_RDD_EOF ; 
 int SMBFS_RDD_FINDFIRST ; 
 int SMBFS_RDD_FINDSINGLE ; 
 int SMBFS_RDD_GOTRNAME ; 
 int SMBFS_RDD_NOCLOSE ; 
 int /*<<< orphan*/  SMB_TRANS2_FIND_FIRST2 ; 
 int /*<<< orphan*/  SMB_TRANS2_FIND_NEXT2 ; 
 int /*<<< orphan*/  SSTOCP (int /*<<< orphan*/ ) ; 
 struct smb_vc* SSTOVC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_init (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int /*<<< orphan*/ ) ; 
 int md_get_uint16 (struct mdchain*,int /*<<< orphan*/ *) ; 
 int md_get_uint16le (struct mdchain*,int*) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int smb_t2_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_t2rq**) ; 
 int /*<<< orphan*/  smb_t2_done (struct smb_t2rq*) ; 
 int smb_t2_request (struct smb_t2rq*) ; 
 int smbfs_fullpath (struct mbchain*,struct smb_vc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static int
smbfs_smb_trans2find2(struct smbfs_fctx *ctx)
{
	struct smb_t2rq *t2p;
	struct smb_vc *vcp = SSTOVC(ctx->f_ssp);
	struct mbchain *mbp;
	struct mdchain *mdp;
	u_int16_t tw, flags;
	int error;

	if (ctx->f_t2) {
		smb_t2_done(ctx->f_t2);
		ctx->f_t2 = NULL;
	}
	ctx->f_flags &= ~SMBFS_RDD_GOTRNAME;
	flags = 8 | 2;			/* <resume> | <close if EOS> */
	if (ctx->f_flags & SMBFS_RDD_FINDSINGLE) {
		flags |= 1;		/* close search after this request */
		ctx->f_flags |= SMBFS_RDD_NOCLOSE;
	}
	if (ctx->f_flags & SMBFS_RDD_FINDFIRST) {
		error = smb_t2_alloc(SSTOCP(ctx->f_ssp), SMB_TRANS2_FIND_FIRST2,
		    ctx->f_scred, &t2p);
		if (error)
			return error;
		ctx->f_t2 = t2p;
		mbp = &t2p->t2_tparam;
		mb_init(mbp);
		mb_put_uint16le(mbp, ctx->f_attrmask);
		mb_put_uint16le(mbp, ctx->f_limit);
		mb_put_uint16le(mbp, flags);
		mb_put_uint16le(mbp, ctx->f_infolevel);
		mb_put_uint32le(mbp, 0);
		error = smbfs_fullpath(mbp, vcp, ctx->f_dnp, ctx->f_wildcard, ctx->f_wclen);
		if (error)
			return error;
	} else	{
		error = smb_t2_alloc(SSTOCP(ctx->f_ssp), SMB_TRANS2_FIND_NEXT2,
		    ctx->f_scred, &t2p);
		if (error)
			return error;
		ctx->f_t2 = t2p;
		mbp = &t2p->t2_tparam;
		mb_init(mbp);
		mb_put_mem(mbp, (caddr_t)&ctx->f_Sid, 2, MB_MSYSTEM);
		mb_put_uint16le(mbp, ctx->f_limit);
		mb_put_uint16le(mbp, ctx->f_infolevel);
		mb_put_uint32le(mbp, 0);		/* resume key */
		mb_put_uint16le(mbp, flags);
		if (ctx->f_rname)
			mb_put_mem(mbp, ctx->f_rname, ctx->f_rnamelen + 1, MB_MSYSTEM);
		else
			mb_put_uint8(mbp, 0);	/* resume file name */
#if 0
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 200 * 1000;	/* 200ms */
		if (vcp->vc_flags & SMBC_WIN95) {
			/*
			 * some implementations suggests to sleep here
			 * for 200ms, due to the bug in the Win95.
			 * I've didn't notice any problem, but put code
			 * for it.
			 */
			 pause("fix95", tvtohz(&tv));
		}
#endif
	}
	t2p->t2_maxpcount = 5 * 2;
	t2p->t2_maxdcount = vcp->vc_txmax;
	error = smb_t2_request(t2p);
	if (error)
		return error;
	mdp = &t2p->t2_rparam;
	if (ctx->f_flags & SMBFS_RDD_FINDFIRST) {
		if ((error = md_get_uint16(mdp, &ctx->f_Sid)) != 0)
			return error;
		ctx->f_flags &= ~SMBFS_RDD_FINDFIRST;
	}
	if ((error = md_get_uint16le(mdp, &tw)) != 0)
		return error;
	ctx->f_ecnt = tw;
	if ((error = md_get_uint16le(mdp, &tw)) != 0)
		return error;
	if (tw)
		ctx->f_flags |= SMBFS_RDD_EOF | SMBFS_RDD_NOCLOSE;
	if ((error = md_get_uint16le(mdp, &tw)) != 0)
		return error;
	if ((error = md_get_uint16le(mdp, &tw)) != 0)
		return error;
	if (ctx->f_ecnt == 0) {
		ctx->f_flags |= SMBFS_RDD_EOF | SMBFS_RDD_NOCLOSE;
		return ENOENT;
	}
	ctx->f_rnameofs = tw;
	mdp = &t2p->t2_rdata;
	if (mdp->md_top == NULL) {
		printf("bug: ecnt = %d, but data is NULL (please report)\n", ctx->f_ecnt);
		return ENOENT;
	}
	if (mdp->md_top->m_len == 0) {
		printf("bug: ecnt = %d, but m_len = 0 and m_next = %p (please report)\n", ctx->f_ecnt,mbp->mb_top->m_next);
		return ENOENT;
	}
	ctx->f_eofs = 0;
	return 0;
}