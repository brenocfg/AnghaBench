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
struct smb_rq {int dummy; } ;
struct smb_ctx {int dummy; } ;
struct mbdata {int dummy; } ;
typedef  int /*<<< orphan*/  smbfh ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_COM_OPEN_PRINT_FILE ; 
 int /*<<< orphan*/  SMB_DT_ASCII ; 
 int /*<<< orphan*/  mb_get_uint16 (struct mbdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbdata*,int) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_dstring (struct mbdata*,char*) ; 
 struct mbdata* smb_rq_getreply (struct smb_rq*) ; 
 struct mbdata* smb_rq_getrequest (struct smb_rq*) ; 
 int smb_rq_init (struct smb_ctx*,int /*<<< orphan*/ ,int,struct smb_rq**) ; 
 int smb_rq_simple (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 

int
smb_smb_open_print_file(struct smb_ctx *ctx, int setuplen, int mode,
	char *ident, smbfh *fhp)
{
	struct smb_rq *rqp;
	struct mbdata *mbp;
	int error;

	error = smb_rq_init(ctx, SMB_COM_OPEN_PRINT_FILE, 2, &rqp);
	if (error)
		return error;
	mbp = smb_rq_getrequest(rqp);
	mb_put_uint16le(mbp, setuplen);
	mb_put_uint16le(mbp, mode);
	smb_rq_wend(rqp);
	mb_put_uint8(mbp, SMB_DT_ASCII);
	smb_rq_dstring(mbp, ident);
	error = smb_rq_simple(rqp);
	if (!error) {
		mbp = smb_rq_getreply(rqp);
		mb_get_uint16(mbp, fhp);
	}
	smb_rq_done(rqp);
	return error;
}