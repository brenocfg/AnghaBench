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
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_2__* spnego_name ;
typedef  int /*<<< orphan*/  ni ;
typedef  TYPE_3__* gssspnego_ctx ;
typedef  scalar_t__ gss_name_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_20__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
typedef  TYPE_4__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_15__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_21__ {TYPE_13__ mechTypes; int /*<<< orphan*/ * mechListMIC; TYPE_14__* mechToken; int /*<<< orphan*/ * reqFlags; } ;
struct TYPE_17__ {int /*<<< orphan*/ * val; scalar_t__ len; } ;
struct TYPE_19__ {int local; scalar_t__ mech_flags; scalar_t__ mech_time_rec; int maybe_open; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  negotiated_mech_type; TYPE_1__ initiator_mech_types; int /*<<< orphan*/  preferred_mech_type; int /*<<< orphan*/  target_name; int /*<<< orphan*/  negotiated_ctx_id; } ;
struct TYPE_18__ {int /*<<< orphan*/  type; int /*<<< orphan*/  value; } ;
struct TYPE_16__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  TYPE_5__ NegTokenInit ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (TYPE_14__*,int) ; 
 int /*<<< orphan*/  ASN1_C_CONTEXT ; 
 int /*<<< orphan*/  CONS ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 scalar_t__ const GSS_C_NO_NAME ; 
 scalar_t__ GSS_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  GSS_SPNEGO_MECHANISM ; 
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTINUE_NEEDED ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ _gss_spnego_alloc_sec_context (scalar_t__*,scalar_t__*) ; 
 scalar_t__ _gss_spnego_indicate_mechtypelist (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _gss_spnego_internal_delete_sec_context (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int der_length_len (size_t) ; 
 int der_put_length_and_tag (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int encode_NegTokenInit (int /*<<< orphan*/ *,size_t,TYPE_5__*,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_NegTokenInit (TYPE_5__*) ; 
 scalar_t__ gss_encapsulate_token (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_import_name (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_init_sec_context (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,TYPE_4__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gss_mg_collect_error (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_4__*) ; 
 int /*<<< orphan*/  initiator_approved ; 
 size_t length_NegTokenInit (TYPE_5__*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OM_uint32
spnego_initial
           (OM_uint32 * minor_status,
	    gss_cred_id_t cred,
            gss_ctx_id_t * context_handle,
            const gss_name_t target_name,
            const gss_OID mech_type,
            OM_uint32 req_flags,
            OM_uint32 time_req,
            const gss_channel_bindings_t input_chan_bindings,
            const gss_buffer_t input_token,
            gss_OID * actual_mech_type,
            gss_buffer_t output_token,
            OM_uint32 * ret_flags,
            OM_uint32 * time_rec
    )
{
    NegTokenInit ni;
    int ret;
    OM_uint32 sub, minor;
    gss_buffer_desc mech_token;
    u_char *buf;
    size_t buf_size, buf_len;
    gss_buffer_desc data;
    size_t ni_len;
    gss_ctx_id_t context;
    gssspnego_ctx ctx;
    spnego_name name = (spnego_name)target_name;

    *minor_status = 0;

    memset (&ni, 0, sizeof(ni));

    *context_handle = GSS_C_NO_CONTEXT;

    if (target_name == GSS_C_NO_NAME)
	return GSS_S_BAD_NAME;

    sub = _gss_spnego_alloc_sec_context(&minor, &context);
    if (GSS_ERROR(sub)) {
	*minor_status = minor;
	return sub;
    }
    ctx = (gssspnego_ctx)context;

    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);

    ctx->local = 1;

    sub = gss_import_name(&minor, &name->value, &name->type, &ctx->target_name);
    if (GSS_ERROR(sub)) {
	*minor_status = minor;
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return sub;
    }

    sub = _gss_spnego_indicate_mechtypelist(&minor,
					    ctx->target_name,
					    initiator_approved,
					    0,
					    cred,
					    &ni.mechTypes,
					    &ctx->preferred_mech_type);
    if (GSS_ERROR(sub)) {
	*minor_status = minor;
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return sub;
    }

    ni.reqFlags = NULL;

    /*
     * If we have a credential handle, use it to select the mechanism
     * that we will use
     */

    /* generate optimistic token */
    sub = gss_init_sec_context(&minor,
			       cred,
			       &ctx->negotiated_ctx_id,
			       ctx->target_name,
			       ctx->preferred_mech_type,
			       req_flags,
			       time_req,
			       input_chan_bindings,
			       input_token,
			       &ctx->negotiated_mech_type,
			       &mech_token,
			       &ctx->mech_flags,
			       &ctx->mech_time_rec);
    if (GSS_ERROR(sub)) {
	free_NegTokenInit(&ni);
	*minor_status = minor;
	gss_mg_collect_error(ctx->preferred_mech_type, sub, minor);
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return sub;
    }
    if (sub == GSS_S_COMPLETE)
	ctx->maybe_open = 1;

    if (mech_token.length != 0) {
	ALLOC(ni.mechToken, 1);
	if (ni.mechToken == NULL) {
	    free_NegTokenInit(&ni);
	    gss_release_buffer(&minor, &mech_token);
	    _gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	    *minor_status = ENOMEM;
	    return GSS_S_FAILURE;
	}
	ni.mechToken->length = mech_token.length;
	ni.mechToken->data = malloc(mech_token.length);
	if (ni.mechToken->data == NULL && mech_token.length != 0) {
	    free_NegTokenInit(&ni);
	    gss_release_buffer(&minor, &mech_token);
	    *minor_status = ENOMEM;
	    _gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	    return GSS_S_FAILURE;
	}
	memcpy(ni.mechToken->data, mech_token.value, mech_token.length);
	gss_release_buffer(&minor, &mech_token);
    } else
	ni.mechToken = NULL;

    ni.mechListMIC = NULL;

    ni_len = length_NegTokenInit(&ni);
    buf_size = 1 + der_length_len(ni_len) + ni_len;

    buf = malloc(buf_size);
    if (buf == NULL) {
	free_NegTokenInit(&ni);
	*minor_status = ENOMEM;
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return GSS_S_FAILURE;
    }

    ret = encode_NegTokenInit(buf + buf_size - 1,
			      ni_len,
			      &ni, &buf_len);
    if (ret == 0 && ni_len != buf_len)
	abort();

    if (ret == 0) {
	size_t tmp;

	ret = der_put_length_and_tag(buf + buf_size - buf_len - 1,
				     buf_size - buf_len,
				     buf_len,
				     ASN1_C_CONTEXT,
				     CONS,
				     0,
				     &tmp);
	if (ret == 0 && tmp + buf_len != buf_size)
	    abort();
    }
    if (ret) {
	*minor_status = ret;
	free(buf);
	free_NegTokenInit(&ni);
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return GSS_S_FAILURE;
    }

    data.value  = buf;
    data.length = buf_size;

    ctx->initiator_mech_types.len = ni.mechTypes.len;
    ctx->initiator_mech_types.val = ni.mechTypes.val;
    ni.mechTypes.len = 0;
    ni.mechTypes.val = NULL;

    free_NegTokenInit(&ni);

    sub = gss_encapsulate_token(&data,
				GSS_SPNEGO_MECHANISM,
				output_token);
    free (buf);

    if (sub) {
	_gss_spnego_internal_delete_sec_context(&minor, &context, GSS_C_NO_BUFFER);
	return sub;
    }

    if (actual_mech_type)
	*actual_mech_type = ctx->negotiated_mech_type;
    if (ret_flags)
	*ret_flags = ctx->mech_flags;
    if (time_rec)
	*time_rec = ctx->mech_time_rec;

    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

    *context_handle = context;

    return GSS_S_CONTINUE_NEEDED;
}