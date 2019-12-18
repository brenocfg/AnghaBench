#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct init_sec_context_res {scalar_t__ major_status; void* time_rec; void* ret_flags; int /*<<< orphan*/  output_token; scalar_t__ ctx; int /*<<< orphan*/  actual_mech_type; void* minor_status; } ;
struct TYPE_21__ {int /*<<< orphan*/ * value; scalar_t__ length; } ;
struct init_sec_context_args {TYPE_5__ input_token; int /*<<< orphan*/  input_chan_bindings; void* time_req; void* req_flags; int /*<<< orphan*/  mech_type; int /*<<< orphan*/  name; scalar_t__ ctx; scalar_t__ cred; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  res ;
typedef  TYPE_2__* gss_name_t ;
typedef  TYPE_3__* gss_ctx_id_t ;
typedef  TYPE_4__* gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  TYPE_5__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_20__ {scalar_t__ handle; } ;
struct TYPE_19__ {scalar_t__ handle; } ;
struct TYPE_18__ {int /*<<< orphan*/  handle; } ;
struct TYPE_17__ {int /*<<< orphan*/  cr_uid; } ;
struct TYPE_16__ {TYPE_1__* td_ucred; } ;
typedef  void* OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 void* GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTINUE_NEEDED ; 
 void* GSS_S_FAILURE ; 
 int /*<<< orphan*/  KGSS_MECH_TYPE (TYPE_3__*) ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct init_sec_context_res*,int) ; 
 TYPE_14__* curthread ; 
 int gssd_init_sec_context_1 (struct init_sec_context_args*,struct init_sec_context_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_copy_buffer (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_3__* kgss_create_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kgss_gssd_client () ; 
 scalar_t__ kgss_transfer_context (TYPE_3__*) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct init_sec_context_res*) ; 
 scalar_t__ xdr_init_sec_context_res ; 

OM_uint32
gss_init_sec_context(OM_uint32 * minor_status,
    const gss_cred_id_t initiator_cred_handle,
    gss_ctx_id_t * context_handle,
    const gss_name_t target_name,
    const gss_OID input_mech_type,
    OM_uint32 req_flags,
    OM_uint32 time_req,
    const gss_channel_bindings_t input_chan_bindings,
    const gss_buffer_t input_token,
    gss_OID * actual_mech_type,
    gss_buffer_t output_token,
    OM_uint32 * ret_flags,
    OM_uint32 * time_rec)
{
	struct init_sec_context_res res;
	struct init_sec_context_args args;
	enum clnt_stat stat;
	gss_ctx_id_t ctx = *context_handle;
	CLIENT *cl;

	*minor_status = 0;

	cl = kgss_gssd_client();
	if (cl == NULL)
		return (GSS_S_FAILURE);

	args.uid = curthread->td_ucred->cr_uid;
	if  (initiator_cred_handle)
		args.cred = initiator_cred_handle->handle;
	else
		args.cred = 0;
	if (ctx)
		args.ctx = ctx->handle;
	else
		args.ctx = 0;
	args.name = target_name->handle;
	args.mech_type = input_mech_type;
	args.req_flags = req_flags;
	args.time_req = time_req;
	args.input_chan_bindings = input_chan_bindings;
	if (input_token)
		args.input_token = *input_token;
	else {
		args.input_token.length = 0;
		args.input_token.value = NULL;
	}

	bzero(&res, sizeof(res));
	stat = gssd_init_sec_context_1(&args, &res, cl);
	CLNT_RELEASE(cl);
	if (stat != RPC_SUCCESS) {
		*minor_status = stat;
		return (GSS_S_FAILURE);
	}

	if (res.major_status != GSS_S_COMPLETE
	    && res.major_status != GSS_S_CONTINUE_NEEDED) {
		*minor_status = res.minor_status;
		xdr_free((xdrproc_t) xdr_init_sec_context_res, &res);
		return (res.major_status);
	}

	*minor_status = res.minor_status;

	if (!ctx) {
		ctx = kgss_create_context(res.actual_mech_type);
		if (!ctx) {
			xdr_free((xdrproc_t) xdr_init_sec_context_res, &res);
			*minor_status = 0;
			return (GSS_S_BAD_MECH);
		}
	}
	*context_handle = ctx;
	ctx->handle = res.ctx;
	if (actual_mech_type)
		*actual_mech_type = KGSS_MECH_TYPE(ctx);
	kgss_copy_buffer(&res.output_token, output_token);
	if (ret_flags)
		*ret_flags = res.ret_flags;
	if (time_rec)
		*time_rec = res.time_rec;

	xdr_free((xdrproc_t) xdr_init_sec_context_res, &res);

	/*
	 * If the context establishment is complete, export it from
	 * userland and hand the result (which includes key material
	 * etc.) to the kernel implementation.
	 */
	if (res.major_status == GSS_S_COMPLETE)
		res.major_status = kgss_transfer_context(ctx);

	return (res.major_status);
}