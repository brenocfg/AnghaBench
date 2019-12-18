#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_21__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_11__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  krb5_flags ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_32__ {int length; int* data; } ;
typedef  TYPE_4__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int32_t ;
typedef  TYPE_5__* gsskrb5_ctx ;
typedef  TYPE_6__* gsskrb5_cred ;
typedef  int /*<<< orphan*/  gss_channel_bindings_t ;
typedef  TYPE_7__* gss_buffer_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_35__ {int* value; int length; } ;
struct TYPE_34__ {int cred_flags; } ;
struct TYPE_33__ {int flags; int more_flags; int /*<<< orphan*/ * ccache; int /*<<< orphan*/  state; TYPE_11__* kcred; TYPE_21__* auth_context; int /*<<< orphan*/ * target; int /*<<< orphan*/  deleg_auth_context; } ;
struct TYPE_31__ {int /*<<< orphan*/  keytype; } ;
struct TYPE_28__ {scalar_t__ ok_as_delegate; } ;
struct TYPE_30__ {TYPE_1__ b; } ;
struct TYPE_29__ {TYPE_3__* keyblock; } ;
struct TYPE_27__ {TYPE_2__ flags; } ;
typedef  int OM_uint32 ;
typedef  int /*<<< orphan*/  Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  AP_OPTS_MUTUAL_REQUIRED ; 
 int CLOSE_CCACHE ; 
 int GSS_CF_NO_CI_FLAGS ; 
 int GSS_C_ANON_FLAG ; 
 int GSS_C_CONF_FLAG ; 
 int GSS_C_DCE_STYLE ; 
 int GSS_C_DELEG_FLAG ; 
 int GSS_C_DELEG_POLICY_FLAG ; 
 int GSS_C_EXTENDED_ERROR_FLAG ; 
 int GSS_C_IDENTIFY_FLAG ; 
 int GSS_C_INTEG_FLAG ; 
 int GSS_C_MUTUAL_FLAG ; 
 int GSS_C_REPLAY_FLAG ; 
 int GSS_C_SEQUENCE_FLAG ; 
 int GSS_C_TRANS_FLAG ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 int GSS_S_CONTINUE_NEEDED ; 
 int GSS_S_FAILURE ; 
 int /*<<< orphan*/  INITIATOR_WAIT_FOR_MUTAL ; 
 int /*<<< orphan*/  KRB5_KU_AP_REQ_AUTH ; 
 int LOCAL ; 
 int _gsskrb5_create_8003_checksum (int*,int /*<<< orphan*/  const,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int _gsskrb5_encapsulate (int*,TYPE_4__*,TYPE_7__*,int*,int /*<<< orphan*/ ) ; 
 int _krb5_build_authenticator (int /*<<< orphan*/ ,TYPE_21__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_11__*,int /*<<< orphan*/ *,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  free_Checksum (int /*<<< orphan*/ *) ; 
 int gsskrb5_initiator_ready (int*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int krb5_build_ap_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ,TYPE_4__,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_cc_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_get_kdc_sec_offset (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_kdc_sec_offset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static OM_uint32
init_auth_restart
(OM_uint32 * minor_status,
 gsskrb5_cred cred,
 gsskrb5_ctx ctx,
 krb5_context context,
 OM_uint32 req_flags,
 const gss_channel_bindings_t input_chan_bindings,
 const gss_buffer_t input_token,
 gss_OID * actual_mech_type,
 gss_buffer_t output_token,
 OM_uint32 * ret_flags,
 OM_uint32 * time_rec
    )
{
    OM_uint32 ret = GSS_S_FAILURE;
    krb5_error_code kret;
    krb5_flags ap_options;
    krb5_data outbuf;
    uint32_t flags;
    krb5_data authenticator;
    Checksum cksum;
    krb5_enctype enctype;
    krb5_data fwd_data, timedata;
    int32_t offset = 0, oldoffset = 0;
    uint32_t flagmask;

    krb5_data_zero(&outbuf);
    krb5_data_zero(&fwd_data);

    *minor_status = 0;

    /*
     * If the credential doesn't have ok-as-delegate, check if there
     * is a realm setting and use that.
     */
    if (!ctx->kcred->flags.b.ok_as_delegate) {
	krb5_data data;

	ret = krb5_cc_get_config(context, ctx->ccache, NULL,
				 "realm-config", &data);
	if (ret == 0) {
	    /* XXX 1 is use ok-as-delegate */
	    if (data.length < 1 || ((((unsigned char *)data.data)[0]) & 1) == 0)
		req_flags &= ~(GSS_C_DELEG_FLAG|GSS_C_DELEG_POLICY_FLAG);
	    krb5_data_free(&data);
	}
    }

    flagmask = 0;

    /* if we used GSS_C_DELEG_POLICY_FLAG, trust KDC */
    if ((req_flags & GSS_C_DELEG_POLICY_FLAG)
	&& ctx->kcred->flags.b.ok_as_delegate)
	flagmask |= GSS_C_DELEG_FLAG | GSS_C_DELEG_POLICY_FLAG;
    /* if there still is a GSS_C_DELEG_FLAG, use that */
    if (req_flags & GSS_C_DELEG_FLAG)
	flagmask |= GSS_C_DELEG_FLAG;


    flags = 0;
    ap_options = 0;
    if (flagmask & GSS_C_DELEG_FLAG) {
	do_delegation (context,
		       ctx->deleg_auth_context,
		       ctx->ccache, ctx->kcred, ctx->target,
		       &fwd_data, flagmask, &flags);
    }

    if (req_flags & GSS_C_MUTUAL_FLAG) {
	flags |= GSS_C_MUTUAL_FLAG;
	ap_options |= AP_OPTS_MUTUAL_REQUIRED;
    }

    if (req_flags & GSS_C_REPLAY_FLAG)
	flags |= GSS_C_REPLAY_FLAG;
    if (req_flags & GSS_C_SEQUENCE_FLAG)
	flags |= GSS_C_SEQUENCE_FLAG;
#if 0
    if (req_flags & GSS_C_ANON_FLAG)
	;                               /* XXX */
#endif
    if (req_flags & GSS_C_DCE_STYLE) {
	/* GSS_C_DCE_STYLE implies GSS_C_MUTUAL_FLAG */
	flags |= GSS_C_DCE_STYLE | GSS_C_MUTUAL_FLAG;
	ap_options |= AP_OPTS_MUTUAL_REQUIRED;
    }
    if (req_flags & GSS_C_IDENTIFY_FLAG)
	flags |= GSS_C_IDENTIFY_FLAG;
    if (req_flags & GSS_C_EXTENDED_ERROR_FLAG)
	flags |= GSS_C_EXTENDED_ERROR_FLAG;

    if (req_flags & GSS_C_CONF_FLAG) {
	flags |= GSS_C_CONF_FLAG;
    }
    if (req_flags & GSS_C_INTEG_FLAG) {
	flags |= GSS_C_INTEG_FLAG;
    }
    if (cred == NULL || !(cred->cred_flags & GSS_CF_NO_CI_FLAGS)) {
	flags |= GSS_C_CONF_FLAG;
	flags |= GSS_C_INTEG_FLAG;
    }
    flags |= GSS_C_TRANS_FLAG;

    if (ret_flags)
	*ret_flags = flags;
    ctx->flags = flags;
    ctx->more_flags |= LOCAL;

    ret = _gsskrb5_create_8003_checksum (minor_status,
					 input_chan_bindings,
					 flags,
					 &fwd_data,
					 &cksum);
    krb5_data_free (&fwd_data);
    if (ret)
	goto failure;

    enctype = ctx->auth_context->keyblock->keytype;

    ret = krb5_cc_get_config(context, ctx->ccache, ctx->target,
			     "time-offset", &timedata);
    if (ret == 0) {
	if (timedata.length == 4) {
	    const u_char *p = timedata.data;
	    offset = (p[0] <<24) | (p[1] << 16) | (p[2] << 8) | (p[3] << 0);
	}
	krb5_data_free(&timedata);
    }

    if (offset) {
	krb5_get_kdc_sec_offset (context, &oldoffset, NULL);
	krb5_set_kdc_sec_offset (context, offset, -1);
    }

    kret = _krb5_build_authenticator(context,
				     ctx->auth_context,
				     enctype,
				     ctx->kcred,
				     &cksum,
				     &authenticator,
				     KRB5_KU_AP_REQ_AUTH);

    if (kret) {
	if (offset)
	    krb5_set_kdc_sec_offset (context, oldoffset, -1);
	*minor_status = kret;
	ret = GSS_S_FAILURE;
	goto failure;
    }

    kret = krb5_build_ap_req (context,
			      enctype,
			      ctx->kcred,
			      ap_options,
			      authenticator,
			      &outbuf);
    if (offset)
	krb5_set_kdc_sec_offset (context, oldoffset, -1);
    if (kret) {
	*minor_status = kret;
	ret = GSS_S_FAILURE;
	goto failure;
    }

    if (flags & GSS_C_DCE_STYLE) {
	output_token->value = outbuf.data;
	output_token->length = outbuf.length;
    } else {
        ret = _gsskrb5_encapsulate (minor_status, &outbuf, output_token,
				    (u_char *)(intptr_t)"\x01\x00",
				    GSS_KRB5_MECHANISM);
	krb5_data_free (&outbuf);
	if (ret)
	    goto failure;
    }

    free_Checksum(&cksum);

    if (flags & GSS_C_MUTUAL_FLAG) {
	ctx->state = INITIATOR_WAIT_FOR_MUTAL;
	return GSS_S_CONTINUE_NEEDED;
    }

    return gsskrb5_initiator_ready(minor_status, ctx, context);
failure:
    if (ctx->ccache && (ctx->more_flags & CLOSE_CCACHE))
	krb5_cc_close(context, ctx->ccache);
    ctx->ccache = NULL;

    return ret;
}