#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  k6_data ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_1__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_2__* gss_buffer_t ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/ * value; } ;
struct TYPE_7__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  auth_context; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_rc4 () ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SIGN ; 
 int LOCAL ; 
 int /*<<< orphan*/ * _gssapi_make_mech_header (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_encap_length (int,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_encode_be_om_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _gsskrb5_release_buffer (scalar_t__*,TYPE_2__*) ; 
 scalar_t__ arcfour_mic_cksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ arcfour_mic_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

OM_uint32
_gssapi_get_mic_arcfour(OM_uint32 * minor_status,
			const gsskrb5_ctx context_handle,
			krb5_context context,
			gss_qop_t qop_req,
			const gss_buffer_t message_buffer,
			gss_buffer_t message_token,
			krb5_keyblock *key)
{
    krb5_error_code ret;
    int32_t seq_number;
    size_t len, total_len;
    u_char k6_data[16], *p0, *p;
    EVP_CIPHER_CTX *rc4_key;

    _gsskrb5_encap_length (22, &len, &total_len, GSS_KRB5_MECHANISM);

    message_token->length = total_len;
    message_token->value  = malloc (total_len);
    if (message_token->value == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    p0 = _gssapi_make_mech_header(message_token->value,
				  len,
				  GSS_KRB5_MECHANISM);
    p = p0;

    *p++ = 0x01; /* TOK_ID */
    *p++ = 0x01;
    *p++ = 0x11; /* SGN_ALG */
    *p++ = 0x00;
    *p++ = 0xff; /* Filler */
    *p++ = 0xff;
    *p++ = 0xff;
    *p++ = 0xff;

    p = NULL;

    ret = arcfour_mic_cksum(context,
			    key, KRB5_KU_USAGE_SIGN,
			    p0 + 16, 8,  /* SGN_CKSUM */
			    p0, 8, /* TOK_ID, SGN_ALG, Filer */
			    message_buffer->value, message_buffer->length,
			    NULL, 0);
    if (ret) {
	_gsskrb5_release_buffer(minor_status, message_token);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    ret = arcfour_mic_key(context, key,
			  p0 + 16, 8, /* SGN_CKSUM */
			  k6_data, sizeof(k6_data));
    if (ret) {
	_gsskrb5_release_buffer(minor_status, message_token);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    krb5_auth_con_getlocalseqnumber (context,
				     context_handle->auth_context,
				     &seq_number);
    p = p0 + 8; /* SND_SEQ */
    _gsskrb5_encode_be_om_uint32(seq_number, p);

    krb5_auth_con_setlocalseqnumber (context,
				     context_handle->auth_context,
				     ++seq_number);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

    memset (p + 4, (context_handle->more_flags & LOCAL) ? 0 : 0xff, 4);

    rc4_key = EVP_CIPHER_CTX_new();
    if (rc4_key == NULL) {
	_gsskrb5_release_buffer(minor_status, message_token);
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    EVP_CipherInit_ex(rc4_key, EVP_rc4(), NULL, k6_data, NULL, 1);
    EVP_Cipher(rc4_key, p, p, 8);
    EVP_CIPHER_CTX_free(rc4_key);

    memset(k6_data, 0, sizeof(k6_data));

    *minor_status = 0;
    return GSS_S_COMPLETE;
}