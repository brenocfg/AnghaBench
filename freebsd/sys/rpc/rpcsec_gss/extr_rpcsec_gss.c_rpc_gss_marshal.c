#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct rpc_pending_request {void* pr_seq; void* pr_xid; } ;
struct rpc_gss_cred {scalar_t__ gc_proc; scalar_t__ gc_svc; void* gc_seq; } ;
struct rpc_gss_data {scalar_t__ gd_state; struct rpc_gss_cred gd_cred; int /*<<< orphan*/  gd_qop; int /*<<< orphan*/  gd_ctx; int /*<<< orphan*/  gd_mech; int /*<<< orphan*/  gd_lock; int /*<<< orphan*/  gd_reqs; } ;
struct opaque_auth {char* oa_base; void* oa_length; void* oa_flavor; } ;
struct mbuf {int dummy; } ;
struct TYPE_5__ {char* value; void* length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  credbuf ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rpc_pending_request*,int /*<<< orphan*/ ) ; 
 int MAX_AUTH_BYTES ; 
 void* RPCSEC_GSS ; 
 scalar_t__ RPCSEC_GSS_CONTINUE_INIT ; 
 scalar_t__ RPCSEC_GSS_ESTABLISHED ; 
 scalar_t__ RPCSEC_GSS_INIT ; 
 int /*<<< orphan*/  RPC_GSS_ER_SYSTEMERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 void* XDR_GETPOS (int /*<<< orphan*/ *) ; 
 char* XDR_INLINE (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct opaque_auth _null_auth ; 
 int /*<<< orphan*/  _rpc_gss_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_get_mic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 struct rpc_pending_request* mem_alloc (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_link ; 
 void* rpc_gss_alloc_seq (struct rpc_gss_data*) ; 
 int /*<<< orphan*/  rpc_gss_destroy_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 int /*<<< orphan*/  rpc_gss_log_status (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ rpc_gss_svc_none ; 
 int /*<<< orphan*/  xdr_opaque_auth (int /*<<< orphan*/ *,struct opaque_auth*) ; 
 int /*<<< orphan*/  xdr_rpc_gss_cred (int /*<<< orphan*/ *,struct rpc_gss_cred*) ; 
 int /*<<< orphan*/  xdr_rpc_gss_wrap_data (struct mbuf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  xdrmbuf_append (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
rpc_gss_marshal(AUTH *auth, uint32_t xid, XDR *xdrs, struct mbuf *args)
{
	struct rpc_gss_data	*gd;
	struct rpc_pending_request *pr;
	uint32_t		 seq;
	XDR			 tmpxdrs;
	struct rpc_gss_cred	 gsscred;
	char			 credbuf[MAX_AUTH_BYTES];
	struct opaque_auth	 creds, verf;
	gss_buffer_desc		 rpcbuf, checksum;
	OM_uint32		 maj_stat, min_stat;
	bool_t			 xdr_stat;

	rpc_gss_log_debug("in rpc_gss_marshal()");

	gd = AUTH_PRIVATE(auth);
	
	gsscred = gd->gd_cred;
	seq = rpc_gss_alloc_seq(gd);
	gsscred.gc_seq = seq;

	xdrmem_create(&tmpxdrs, credbuf, sizeof(credbuf), XDR_ENCODE);
	if (!xdr_rpc_gss_cred(&tmpxdrs, &gsscred)) {
		XDR_DESTROY(&tmpxdrs);
		_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOMEM);
		return (FALSE);
	}
	creds.oa_flavor = RPCSEC_GSS;
	creds.oa_base = credbuf;
	creds.oa_length = XDR_GETPOS(&tmpxdrs);
	XDR_DESTROY(&tmpxdrs);

	xdr_opaque_auth(xdrs, &creds);

	if (gd->gd_cred.gc_proc == RPCSEC_GSS_INIT ||
	    gd->gd_cred.gc_proc == RPCSEC_GSS_CONTINUE_INIT) {
		if (!xdr_opaque_auth(xdrs, &_null_auth)) {
			_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOMEM);
			return (FALSE);
		}
		xdrmbuf_append(xdrs, args);
		return (TRUE);
	} else {
		/*
		 * Keep track of this XID + seq pair so that we can do
		 * the matching gss_verify_mic in AUTH_VALIDATE.
		 */
		pr = mem_alloc(sizeof(struct rpc_pending_request));
		mtx_lock(&gd->gd_lock);
		pr->pr_xid = xid;
		pr->pr_seq = seq;
		LIST_INSERT_HEAD(&gd->gd_reqs, pr, pr_link);
		mtx_unlock(&gd->gd_lock);

		/*
		 * Checksum serialized RPC header, up to and including
		 * credential. For the in-kernel environment, we
		 * assume that our XDR stream is on a contiguous
		 * memory buffer (e.g. an mbuf).
		 */
		rpcbuf.length = XDR_GETPOS(xdrs);
		XDR_SETPOS(xdrs, 0);
		rpcbuf.value = XDR_INLINE(xdrs, rpcbuf.length);

		maj_stat = gss_get_mic(&min_stat, gd->gd_ctx, gd->gd_qop,
		    &rpcbuf, &checksum);

		if (maj_stat != GSS_S_COMPLETE) {
			rpc_gss_log_status("gss_get_mic", gd->gd_mech,
			    maj_stat, min_stat);
			if (maj_stat == GSS_S_CONTEXT_EXPIRED) {
				rpc_gss_destroy_context(auth, TRUE);
			}
			_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, EPERM);
			return (FALSE);
		}

		verf.oa_flavor = RPCSEC_GSS;
		verf.oa_base = checksum.value;
		verf.oa_length = checksum.length;

		xdr_stat = xdr_opaque_auth(xdrs, &verf);
		gss_release_buffer(&min_stat, &checksum);
		if (!xdr_stat) {
			_rpc_gss_set_error(RPC_GSS_ER_SYSTEMERROR, ENOMEM);
			return (FALSE);
		}
		if (gd->gd_state != RPCSEC_GSS_ESTABLISHED ||
		    gd->gd_cred.gc_svc == rpc_gss_svc_none) {
			xdrmbuf_append(xdrs, args);
			return (TRUE);
		} else {
			if (!xdr_rpc_gss_wrap_data(&args,
				gd->gd_ctx, gd->gd_qop, gd->gd_cred.gc_svc,
				seq))
				return (FALSE);
			xdrmbuf_append(xdrs, args);
			return (TRUE);
		}
	}

	return (TRUE);
}