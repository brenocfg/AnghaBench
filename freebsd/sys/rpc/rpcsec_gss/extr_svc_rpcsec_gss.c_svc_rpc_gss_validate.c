#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct svc_rpc_gss_client {int /*<<< orphan*/  cl_state; int /*<<< orphan*/  cl_mech; int /*<<< orphan*/  cl_ctx; } ;
struct TYPE_6__ {int oa_length; int /*<<< orphan*/ * oa_base; } ;
struct opaque_auth {scalar_t__ oa_length; int /*<<< orphan*/  oa_base; int /*<<< orphan*/  oa_flavor; } ;
struct TYPE_7__ {TYPE_1__ cb_verf; struct opaque_auth cb_cred; scalar_t__ cb_proc; scalar_t__ cb_vers; scalar_t__ cb_prog; scalar_t__ cb_rpcvers; } ;
struct rpc_msg {TYPE_2__ rm_call; int /*<<< orphan*/  rm_direction; scalar_t__ rm_xid; } ;
typedef  int /*<<< orphan*/  rpchdr ;
typedef  scalar_t__ rpc_gss_proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_3__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_STALE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  IXDR_PUT_ENUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXDR_PUT_LONG (int /*<<< orphan*/ *,scalar_t__) ; 
 int RNDUP (scalar_t__) ; 
 scalar_t__ RPCSEC_GSS_DESTROY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_verify_mic (scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 int /*<<< orphan*/  rpc_gss_log_status (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool_t
svc_rpc_gss_validate(struct svc_rpc_gss_client *client, struct rpc_msg *msg,
    gss_qop_t *qop, rpc_gss_proc_t gcproc)
{
	struct opaque_auth	*oa;
	gss_buffer_desc		 rpcbuf, checksum;
	OM_uint32		 maj_stat, min_stat;
	gss_qop_t		 qop_state;
	int32_t			 rpchdr[128 / sizeof(int32_t)];
	int32_t			*buf;

	rpc_gss_log_debug("in svc_rpc_gss_validate()");
	
	memset(rpchdr, 0, sizeof(rpchdr));

	/* Reconstruct RPC header for signing (from xdr_callmsg). */
	buf = rpchdr;
	IXDR_PUT_LONG(buf, msg->rm_xid);
	IXDR_PUT_ENUM(buf, msg->rm_direction);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_rpcvers);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_prog);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_vers);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_proc);
	oa = &msg->rm_call.cb_cred;
	IXDR_PUT_ENUM(buf, oa->oa_flavor);
	IXDR_PUT_LONG(buf, oa->oa_length);
	if (oa->oa_length) {
		memcpy((caddr_t)buf, oa->oa_base, oa->oa_length);
		buf += RNDUP(oa->oa_length) / sizeof(int32_t);
	}
	rpcbuf.value = rpchdr;
	rpcbuf.length = (u_char *)buf - (u_char *)rpchdr;

	checksum.value = msg->rm_call.cb_verf.oa_base;
	checksum.length = msg->rm_call.cb_verf.oa_length;
	
	maj_stat = gss_verify_mic(&min_stat, client->cl_ctx, &rpcbuf, &checksum,
				  &qop_state);
	
	if (maj_stat != GSS_S_COMPLETE) {
		rpc_gss_log_status("gss_verify_mic", client->cl_mech,
		    maj_stat, min_stat);
		/*
		 * A bug in some versions of the Linux client generates a
		 * Destroy operation with a bogus encrypted checksum. Deleting
		 * the credential handle for that case causes the mount to fail.
		 * Since the checksum is bogus (gss_verify_mic() failed), it
		 * doesn't make sense to destroy the handle and not doing so
		 * fixes the Linux mount.
		 */
		if (gcproc != RPCSEC_GSS_DESTROY)
			client->cl_state = CLIENT_STALE;
		return (FALSE);
	}

	*qop = qop_state;
	return (TRUE);
}