#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct accept_sec_context_res {scalar_t__ major_status; int minor_status; int ret_flags; int time_rec; scalar_t__ delegated_cred_handle; int /*<<< orphan*/  output_token; int /*<<< orphan*/  src_name; scalar_t__ ctx; int /*<<< orphan*/  mech_type; } ;
struct accept_sec_context_args {int /*<<< orphan*/  input_chan_bindings; int /*<<< orphan*/  input_token; scalar_t__ cred; scalar_t__ ctx; } ;
struct _gss_name_t {int dummy; } ;
struct _gss_cred_id_t {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_1__* gss_name_t ;
typedef  TYPE_2__* gss_ctx_id_t ;
typedef  TYPE_3__* gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  int /*<<< orphan*/ * gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_15__ {scalar_t__ handle; } ;
struct TYPE_14__ {scalar_t__ handle; } ;
struct TYPE_13__ {int /*<<< orphan*/  handle; } ;
typedef  int OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTINUE_NEEDED ; 
 int GSS_S_FAILURE ; 
 int /*<<< orphan*/  KGSS_MECH_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct accept_sec_context_res*,int) ; 
 int /*<<< orphan*/  gss_release_cred (int*,TYPE_3__**) ; 
 int /*<<< orphan*/  gss_release_name (int*,TYPE_1__**) ; 
 int gssd_accept_sec_context_1 (struct accept_sec_context_args*,struct accept_sec_context_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_copy_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* kgss_create_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 scalar_t__ kgss_transfer_context (TYPE_2__*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_accept_sec_context_res ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct accept_sec_context_res*) ; 

OM_uint32 gss_accept_sec_context(OM_uint32 *minor_status,
    gss_ctx_id_t *context_handle,
    const gss_cred_id_t acceptor_cred_handle,
    const gss_buffer_t input_token,
    const gss_channel_bindings_t input_chan_bindings,
    gss_name_t *src_name,
    gss_OID *mech_type,
    gss_buffer_t output_token,
    OM_uint32 *ret_flags,
    OM_uint32 *time_rec,
    gss_cred_id_t *delegated_cred_handle)
{
	struct accept_sec_context_res res;
	struct accept_sec_context_args args;
	enum clnt_stat stat;
	gss_ctx_id_t ctx = *context_handle;
	gss_name_t name;
	gss_cred_id_t cred;
	CLIENT *cl;

	cl = kgss_gssd_client();
	if (cl == NULL) {
		*minor_status = 0;
		return (GSS_S_FAILURE);
	}

	if (ctx)
		args.ctx = ctx->handle;
	else
		args.ctx = 0;
	if (acceptor_cred_handle)
		args.cred = acceptor_cred_handle->handle;
	else
		args.cred = 0;
	args.input_token = *input_token;
	args.input_chan_bindings = input_chan_bindings;

	bzero(&res, sizeof(res));
	stat = gssd_accept_sec_context_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE
	    && res.major_status != GSS_S_CONTINUE_NEEDED) {
		*minor_status = res.minor_status;
		xdr_free((xdrproc_t) xdr_accept_sec_context_res, &res);
		return (res.major_status);
	}

	*minor_status = res.minor_status;

	if (!ctx) {
		ctx = kgss_create_context(res.mech_type);
		if (!ctx) {
			xdr_free((xdrproc_t) xdr_accept_sec_context_res, &res);
			*minor_status = 0;
			return (GSS_S_BAD_MECH);
		}
	}
	*context_handle = ctx;

	ctx->handle = res.ctx;
	name = malloc(sizeof(struct _gss_name_t), M_GSSAPI, M_WAITOK);
	name->handle = res.src_name;
	if (src_name) {
		*src_name = name;
	} else {
		OM_uint32 junk;
		gss_release_name(&junk, &name);
	}
	if (mech_type)
		*mech_type = KGSS_MECH_TYPE(ctx);
	kgss_copy_buffer(&res.output_token, output_token);
	if (ret_flags)
		*ret_flags = res.ret_flags;
	if (time_rec)
		*time_rec = res.time_rec;
	cred = malloc(sizeof(struct _gss_cred_id_t), M_GSSAPI, M_WAITOK);
	cred->handle = res.delegated_cred_handle;
	if (delegated_cred_handle) {
		*delegated_cred_handle = cred;
	} else {
		OM_uint32 junk;
		gss_release_cred(&junk, &cred);
	}

	xdr_free((xdrproc_t) xdr_accept_sec_context_res, &res);

	/*
	 * If the context establishment is complete, export it from
	 * userland and hand the result (which includes key material
	 * etc.) to the kernel implementation.
	 */
	if (res.major_status == GSS_S_COMPLETE)
		res.major_status = kgss_transfer_context(ctx);

	return (res.major_status);
}