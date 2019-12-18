#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct TYPE_6__ {int fa_size; int fa_attr; int /*<<< orphan*/  fa_ctime; int /*<<< orphan*/  fa_mtime; int /*<<< orphan*/  fa_atime; } ;
struct smbfs_fctx {scalar_t__ f_ecnt; int f_flags; int f_left; int f_limit; int f_infolevel; char* f_name; int f_eofs; int f_rnameofs; int f_rnamelen; int f_nmlen; scalar_t__* f_rname; int /*<<< orphan*/  f_ssp; TYPE_2__ f_attr; struct smb_t2rq* f_t2; } ;
struct mdchain {int dummy; } ;
struct smb_t2rq {struct mdchain t2_rdata; } ;
typedef  int int64_t ;
struct TYPE_5__ {int sv_tz; } ;
struct TYPE_7__ {TYPE_1__ vc_sopt; } ;

/* Variables and functions */
 int EBADRPC ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  M_SMBFSDATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBERROR (char*,...) ; 
 int SMBFS_RDD_EOF ; 
 int SMBFS_RDD_GOTRNAME ; 
#define  SMB_FIND_FILE_DIRECTORY_INFO 129 
#define  SMB_INFO_STANDARD 128 
 int SMB_MAXFNAMELEN ; 
 scalar_t__ SMB_UNICODE_STRINGS (TYPE_3__*) ; 
 TYPE_3__* SSTOVC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_get_int64 (struct mdchain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_get_int64le (struct mdchain*,int*) ; 
 int md_get_mem (struct mdchain*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_get_uint16le (struct mdchain*,int*) ; 
 int /*<<< orphan*/  md_get_uint32 (struct mdchain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_get_uint32le (struct mdchain*,int*) ; 
 int /*<<< orphan*/  md_get_uint8 (struct mdchain*,int*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  smb_dos2unixtime (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_time_NT2local (int,int,int /*<<< orphan*/ *) ; 
 int smbfs_smb_trans2find2 (struct smbfs_fctx*) ; 

__attribute__((used)) static int
smbfs_findnextLM2(struct smbfs_fctx *ctx, int limit)
{
	struct mdchain *mbp;
	struct smb_t2rq *t2p;
	char *cp;
	u_int8_t tb;
	u_int16_t date, time, wattr;
	u_int32_t size, next, dattr;
	int64_t lint;
	int error, svtz, cnt, fxsz, nmlen, recsz;

	if (ctx->f_ecnt == 0) {
		if (ctx->f_flags & SMBFS_RDD_EOF)
			return ENOENT;
		ctx->f_left = ctx->f_limit = limit;
		error = smbfs_smb_trans2find2(ctx);
		if (error)
			return error;
	}
	t2p = ctx->f_t2;
	mbp = &t2p->t2_rdata;
	svtz = SSTOVC(ctx->f_ssp)->vc_sopt.sv_tz;
	switch (ctx->f_infolevel) {
	    case SMB_INFO_STANDARD:
		next = 0;
		fxsz = 0;
		md_get_uint16le(mbp, &date);
		md_get_uint16le(mbp, &time);	/* creation time */
		md_get_uint16le(mbp, &date);
		md_get_uint16le(mbp, &time);	/* access time */
		smb_dos2unixtime(date, time, 0, svtz, &ctx->f_attr.fa_atime);
		md_get_uint16le(mbp, &date);
		md_get_uint16le(mbp, &time);	/* access time */
		smb_dos2unixtime(date, time, 0, svtz, &ctx->f_attr.fa_mtime);
		md_get_uint32le(mbp, &size);
		ctx->f_attr.fa_size = size;
		md_get_uint32(mbp, NULL);	/* allocation size */
		md_get_uint16le(mbp, &wattr);
		ctx->f_attr.fa_attr = wattr;
		md_get_uint8(mbp, &tb);
		size = nmlen = tb;
		fxsz = 23;
		recsz = next = 24 + nmlen;	/* docs misses zero byte at end */
		break;
	    case SMB_FIND_FILE_DIRECTORY_INFO:
		md_get_uint32le(mbp, &next);
		md_get_uint32(mbp, NULL);	/* file index */
		md_get_int64(mbp, NULL);	/* creation time */
		md_get_int64le(mbp, &lint);
		smb_time_NT2local(lint, svtz, &ctx->f_attr.fa_atime);
		md_get_int64le(mbp, &lint);
		smb_time_NT2local(lint, svtz, &ctx->f_attr.fa_mtime);
		md_get_int64le(mbp, &lint);
		smb_time_NT2local(lint, svtz, &ctx->f_attr.fa_ctime);
		md_get_int64le(mbp, &lint);	/* file size */
		ctx->f_attr.fa_size = lint;
		md_get_int64(mbp, NULL);	/* real size (should use) */
		md_get_uint32le(mbp, &dattr);	/* EA */
		ctx->f_attr.fa_attr = dattr;
		md_get_uint32le(mbp, &size);	/* name len */
		fxsz = 64;
		recsz = next ? next : fxsz + size;
		break;
	    default:
		SMBERROR("unexpected info level %d\n", ctx->f_infolevel);
		return EINVAL;
	}
	if (SMB_UNICODE_STRINGS(SSTOVC(ctx->f_ssp))) {
		nmlen = min(size, SMB_MAXFNAMELEN * 2);
	} else
		nmlen = min(size, SMB_MAXFNAMELEN);
	cp = ctx->f_name;
	error = md_get_mem(mbp, cp, nmlen, MB_MSYSTEM);
	if (error)
		return error;
	if (next) {
		cnt = next - nmlen - fxsz;
		if (cnt > 0)
			md_get_mem(mbp, NULL, cnt, MB_MSYSTEM);
		else if (cnt < 0) {
			SMBERROR("out of sync\n");
			return EBADRPC;
		}
	}
	if (SMB_UNICODE_STRINGS(SSTOVC(ctx->f_ssp))) {
		if (nmlen > 1 && cp[nmlen - 1] == 0 && cp[nmlen - 2] == 0)
			nmlen -= 2;
	} else
		if (nmlen && cp[nmlen - 1] == 0)
			nmlen--;
	if (nmlen == 0)
		return EBADRPC;

	next = ctx->f_eofs + recsz;
	if (ctx->f_rnameofs && (ctx->f_flags & SMBFS_RDD_GOTRNAME) == 0 &&
	    (ctx->f_rnameofs >= ctx->f_eofs && ctx->f_rnameofs < next)) {
		/*
		 * Server needs a resume filename.
		 */
		if (ctx->f_rnamelen <= nmlen) {
			if (ctx->f_rname)
				free(ctx->f_rname, M_SMBFSDATA);
			ctx->f_rname = malloc(nmlen + 1, M_SMBFSDATA, M_WAITOK);
			ctx->f_rnamelen = nmlen;
		}
		bcopy(ctx->f_name, ctx->f_rname, nmlen);
		ctx->f_rname[nmlen] = 0;
		ctx->f_flags |= SMBFS_RDD_GOTRNAME;
	}
	ctx->f_nmlen = nmlen;
	ctx->f_eofs = next;
	ctx->f_ecnt--;
	ctx->f_left--;
	return 0;
}