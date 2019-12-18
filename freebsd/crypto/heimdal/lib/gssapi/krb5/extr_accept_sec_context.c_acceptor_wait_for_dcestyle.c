#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ap_rep_enc_part ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  gsskrb5_name ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  TYPE_3__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_11__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {scalar_t__ flags; int /*<<< orphan*/  auth_context; int /*<<< orphan*/  source; int /*<<< orphan*/  lifetime; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ GSS_S_UNSEQ_TOKEN ; 
 int /*<<< orphan*/  KRB5_AUTH_CONTEXT_DO_TIME ; 
 scalar_t__ _gsskrb5_lifetime_left (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ gsskrb5_acceptor_ready (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ krb5_auth_con_getremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_auth_con_removeflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_auth_con_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_auth_con_setremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_ap_rep_enc_part (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_rd_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static OM_uint32
acceptor_wait_for_dcestyle(OM_uint32 * minor_status,
			   gsskrb5_ctx ctx,
			   krb5_context context,
			   const gss_cred_id_t acceptor_cred_handle,
			   const gss_buffer_t input_token_buffer,
			   const gss_channel_bindings_t input_chan_bindings,
			   gss_name_t * src_name,
			   gss_OID * mech_type,
			   gss_buffer_t output_token,
			   OM_uint32 * ret_flags,
			   OM_uint32 * time_rec,
			   gss_cred_id_t * delegated_cred_handle)
{
    OM_uint32 ret;
    krb5_error_code kret;
    krb5_data inbuf;
    int32_t r_seq_number, l_seq_number;

    /*
     * We know it's GSS_C_DCE_STYLE so we don't need to decapsulate the AP_REP
     */

    inbuf.length = input_token_buffer->length;
    inbuf.data = input_token_buffer->value;

    /*
     * We need to remeber the old remote seq_number, then check if the
     * client has replied with our local seq_number, and then reset
     * the remote seq_number to the old value
     */
    {
	kret = krb5_auth_con_getlocalseqnumber(context,
					       ctx->auth_context,
					       &l_seq_number);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}

	kret = krb5_auth_con_getremoteseqnumber(context,
						ctx->auth_context,
						&r_seq_number);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}

	kret = krb5_auth_con_setremoteseqnumber(context,
						ctx->auth_context,
						l_seq_number);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}
    }

    /*
     * We need to verify the AP_REP, but we need to flag that this is
     * DCE_STYLE, so don't check the timestamps this time, but put the
     * flag DO_TIME back afterward.
    */
    {
	krb5_ap_rep_enc_part *repl;
	int32_t auth_flags;

	krb5_auth_con_removeflags(context,
				  ctx->auth_context,
				  KRB5_AUTH_CONTEXT_DO_TIME,
				  &auth_flags);

	kret = krb5_rd_rep(context, ctx->auth_context, &inbuf, &repl);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}
	krb5_free_ap_rep_enc_part(context, repl);
	krb5_auth_con_setflags(context, ctx->auth_context, auth_flags);
    }

    /* We need to check the liftime */
    {
	OM_uint32 lifetime_rec;

	ret = _gsskrb5_lifetime_left(minor_status,
				     context,
				     ctx->lifetime,
				     &lifetime_rec);
	if (ret) {
	    return ret;
	}
	if (lifetime_rec == 0) {
	    return GSS_S_CONTEXT_EXPIRED;
	}

	if (time_rec) *time_rec = lifetime_rec;
    }

    /* We need to give the caller the flags which are in use */
    if (ret_flags) *ret_flags = ctx->flags;

    if (src_name) {
	kret = krb5_copy_principal(context,
				   ctx->source,
				   (gsskrb5_name*)src_name);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}
    }

    /*
     * After the krb5_rd_rep() the remote and local seq_number should
     * be the same, because the client just replies the seq_number
     * from our AP-REP in its AP-REP, but then the client uses the
     * seq_number from its AP-REQ for GSS_wrap()
     */
    {
	int32_t tmp_r_seq_number, tmp_l_seq_number;

	kret = krb5_auth_con_getremoteseqnumber(context,
						ctx->auth_context,
						&tmp_r_seq_number);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}

	kret = krb5_auth_con_getlocalseqnumber(context,
					       ctx->auth_context,
					       &tmp_l_seq_number);
	if (kret) {

	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}

	/*
	 * Here we check if the client has responsed with our local seq_number,
	 */
	if (tmp_r_seq_number != tmp_l_seq_number) {
	    return GSS_S_UNSEQ_TOKEN;
	}
    }

    /*
     * We need to reset the remote seq_number, because the client will use,
     * the old one for the GSS_wrap() calls
     */
    {
	kret = krb5_auth_con_setremoteseqnumber(context,
						ctx->auth_context,
						r_seq_number);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}
    }

    return gsskrb5_acceptor_ready(minor_status, ctx, context,
				  delegated_cred_handle);
}