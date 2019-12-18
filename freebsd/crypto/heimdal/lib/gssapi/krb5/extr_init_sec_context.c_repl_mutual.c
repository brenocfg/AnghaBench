#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
struct TYPE_15__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ap_rep_enc_part ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  TYPE_3__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_17__ {int /*<<< orphan*/ * value; scalar_t__ length; } ;
struct TYPE_16__ {scalar_t__ flags; int /*<<< orphan*/  auth_context; int /*<<< orphan*/  lifetime; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_DCE_STYLE ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ IS_DCE_STYLE (TYPE_2__*) ; 
 scalar_t__ _gsskrb5_decapsulate (scalar_t__*,TYPE_3__* const,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _gsskrb5_lifetime_left (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ gsskrb5_initiator_ready (scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ handle_error_packet (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_getremoteseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_ap_rep_enc_part (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_mk_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_rd_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static OM_uint32
repl_mutual
(OM_uint32 * minor_status,
 gsskrb5_ctx ctx,
 krb5_context context,
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
    OM_uint32 ret;
    krb5_error_code kret;
    krb5_data indata;
    krb5_ap_rep_enc_part *repl;

    output_token->length = 0;
    output_token->value = NULL;

    if (actual_mech_type)
	*actual_mech_type = GSS_KRB5_MECHANISM;

    if (IS_DCE_STYLE(ctx)) {
	/* There is no OID wrapping. */
	indata.length	= input_token->length;
	indata.data	= input_token->value;
	kret = krb5_rd_rep(context,
			   ctx->auth_context,
			   &indata,
			   &repl);
	if (kret) {
	    ret = _gsskrb5_decapsulate(minor_status,
				       input_token,
				       &indata,
				       "\x03\x00",
				       GSS_KRB5_MECHANISM);
	    if (ret == GSS_S_COMPLETE) {
		*minor_status = handle_error_packet(context, ctx, indata);
	    } else {
		*minor_status = kret;
	    }
	    return GSS_S_FAILURE;
	}
    } else {
	ret = _gsskrb5_decapsulate (minor_status,
				    input_token,
				    &indata,
				    "\x02\x00",
				    GSS_KRB5_MECHANISM);
	if (ret == GSS_S_DEFECTIVE_TOKEN) {
	    /* check if there is an error token sent instead */
	    ret = _gsskrb5_decapsulate (minor_status,
					input_token,
					&indata,
					"\x03\x00",
					GSS_KRB5_MECHANISM);
	    if (ret == GSS_S_COMPLETE) {
		*minor_status = handle_error_packet(context, ctx, indata);
		return GSS_S_FAILURE;
	    }
	}
	kret = krb5_rd_rep (context,
			    ctx->auth_context,
			    &indata,
			    &repl);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}
    }

    krb5_free_ap_rep_enc_part (context,
			       repl);

    *minor_status = 0;
    if (time_rec) {
	ret = _gsskrb5_lifetime_left(minor_status,
				     context,
				     ctx->lifetime,
				     time_rec);
    } else {
	ret = GSS_S_COMPLETE;
    }
    if (ret_flags)
	*ret_flags = ctx->flags;

    if (req_flags & GSS_C_DCE_STYLE) {
	int32_t local_seq, remote_seq;
	krb5_data outbuf;

	/*
	 * So DCE_STYLE is strange. The client echos the seq number
	 * that the server used in the server's mk_rep in its own
	 * mk_rep(). After when done, it resets to it's own seq number
	 * for the gss_wrap calls.
	 */

	krb5_auth_con_getremoteseqnumber(context, ctx->auth_context, &remote_seq);
	krb5_auth_con_getlocalseqnumber(context, ctx->auth_context, &local_seq);
	krb5_auth_con_setlocalseqnumber(context, ctx->auth_context, remote_seq);

	kret = krb5_mk_rep(context, ctx->auth_context, &outbuf);
	if (kret) {
	    *minor_status = kret;
	    return GSS_S_FAILURE;
	}

	/* reset local seq number */
	krb5_auth_con_setlocalseqnumber(context, ctx->auth_context, local_seq);

	output_token->length = outbuf.length;
	output_token->value  = outbuf.data;
    }

    return gsskrb5_initiator_ready(minor_status, ctx, context);
}