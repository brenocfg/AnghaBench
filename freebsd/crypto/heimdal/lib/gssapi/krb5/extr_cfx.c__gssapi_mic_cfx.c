#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int* TOK_ID; int /*<<< orphan*/ * SND_SEQ; int /*<<< orphan*/  Filler; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_2__ u_char ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_2__* gss_cfx_mic_token ;
typedef  TYPE_5__* gss_buffer_t ;
struct TYPE_16__ {int length; TYPE_2__* data; } ;
struct TYPE_20__ {TYPE_1__ checksum; } ;
struct TYPE_19__ {int length; TYPE_2__* value; } ;
struct TYPE_18__ {int more_flags; int /*<<< orphan*/  crypto; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  auth_context; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  TYPE_6__ Checksum ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
 int /*<<< orphan*/  CFXAcceptorSubkey ; 
 int /*<<< orphan*/  CFXSentByAcceptor ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 unsigned int KRB5_KU_USAGE_ACCEPTOR_SIGN ; 
 unsigned int KRB5_KU_USAGE_INITIATOR_SIGN ; 
 int LOCAL ; 
 int /*<<< orphan*/  _gsskrb5_encode_be_om_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_Checksum (TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_create_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_2__*,size_t,TYPE_6__*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

OM_uint32 _gssapi_mic_cfx(OM_uint32 *minor_status,
			  const gsskrb5_ctx ctx,
			  krb5_context context,
			  gss_qop_t qop_req,
			  const gss_buffer_t message_buffer,
			  gss_buffer_t message_token)
{
    gss_cfx_mic_token token;
    krb5_error_code ret;
    unsigned usage;
    Checksum cksum;
    u_char *buf;
    size_t len;
    int32_t seq_number;

    len = message_buffer->length + sizeof(*token);
    buf = malloc(len);
    if (buf == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    memcpy(buf, message_buffer->value, message_buffer->length);

    token = (gss_cfx_mic_token)(buf + message_buffer->length);
    token->TOK_ID[0] = 0x04;
    token->TOK_ID[1] = 0x04;
    token->Flags = 0;
    if ((ctx->more_flags & LOCAL) == 0)
	token->Flags |= CFXSentByAcceptor;
    if (ctx->more_flags & ACCEPTOR_SUBKEY)
	token->Flags |= CFXAcceptorSubkey;
    memset(token->Filler, 0xFF, 5);

    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);
    krb5_auth_con_getlocalseqnumber(context,
				    ctx->auth_context,
				    &seq_number);
    _gsskrb5_encode_be_om_uint32(0,          &token->SND_SEQ[0]);
    _gsskrb5_encode_be_om_uint32(seq_number, &token->SND_SEQ[4]);
    krb5_auth_con_setlocalseqnumber(context,
				    ctx->auth_context,
				    ++seq_number);
    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

    if (ctx->more_flags & LOCAL) {
	usage = KRB5_KU_USAGE_INITIATOR_SIGN;
    } else {
	usage = KRB5_KU_USAGE_ACCEPTOR_SIGN;
    }

    ret = krb5_create_checksum(context, ctx->crypto,
	usage, 0, buf, len, &cksum);
    if (ret != 0) {
	*minor_status = ret;
	free(buf);
	return GSS_S_FAILURE;
    }

    /* Determine MIC length */
    message_token->length = sizeof(*token) + cksum.checksum.length;
    message_token->value = malloc(message_token->length);
    if (message_token->value == NULL) {
	*minor_status = ENOMEM;
	free_Checksum(&cksum);
	free(buf);
	return GSS_S_FAILURE;
    }

    /* Token is { "header" | get_mic("header" | plaintext-data) } */
    memcpy(message_token->value, token, sizeof(*token));
    memcpy((u_char *)message_token->value + sizeof(*token),
	   cksum.checksum.data, cksum.checksum.length);

    free_Checksum(&cksum);
    free(buf);

    *minor_status = 0;
    return GSS_S_COMPLETE;
}