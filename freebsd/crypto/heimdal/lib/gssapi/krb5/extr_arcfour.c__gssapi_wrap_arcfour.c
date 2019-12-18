#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_13__ {int* data; int length; } ;
struct TYPE_14__ {TYPE_1__ keyvalue; int /*<<< orphan*/  keytype; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  k6_data ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_16__ {size_t length; int /*<<< orphan*/ * value; } ;
struct TYPE_15__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  auth_context; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  Klocaldata ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_rc4 () ; 
 size_t GSS_ARCFOUR_WRAP_TOKEN_SIZE ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_DCE_STYLE (TYPE_3__* const) ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SEAL ; 
 int LOCAL ; 
 int /*<<< orphan*/  _gssapi_encap_length (size_t,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int* _gssapi_make_mech_header (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_encode_be_om_uint32 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _gsskrb5_release_buffer (scalar_t__*,TYPE_4__*) ; 
 scalar_t__ arcfour_mic_cksum (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*,int,int*,int,int*,int,int*,size_t) ; 
 scalar_t__ arcfour_mic_key (int /*<<< orphan*/ ,TYPE_2__*,int*,int,int*,int) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_generate_random_block (int*,int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

OM_uint32
_gssapi_wrap_arcfour(OM_uint32 * minor_status,
		     const gsskrb5_ctx context_handle,
		     krb5_context context,
		     int conf_req_flag,
		     gss_qop_t qop_req,
		     const gss_buffer_t input_message_buffer,
		     int * conf_state,
		     gss_buffer_t output_message_buffer,
		     krb5_keyblock *key)
{
    u_char Klocaldata[16], k6_data[16], *p, *p0;
    size_t len, total_len, datalen;
    krb5_keyblock Klocal;
    krb5_error_code ret;
    int32_t seq_number;

    if (conf_state)
	*conf_state = 0;

    datalen = input_message_buffer->length;

    if (IS_DCE_STYLE(context_handle)) {
	len = GSS_ARCFOUR_WRAP_TOKEN_SIZE;
	_gssapi_encap_length(len, &len, &total_len, GSS_KRB5_MECHANISM);
	total_len += datalen;
    } else {
	datalen += 1; /* padding */
	len = datalen + GSS_ARCFOUR_WRAP_TOKEN_SIZE;
	_gssapi_encap_length(len, &len, &total_len, GSS_KRB5_MECHANISM);
    }

    output_message_buffer->length = total_len;
    output_message_buffer->value  = malloc (total_len);
    if (output_message_buffer->value == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    p0 = _gssapi_make_mech_header(output_message_buffer->value,
				  len,
				  GSS_KRB5_MECHANISM);
    p = p0;

    *p++ = 0x02; /* TOK_ID */
    *p++ = 0x01;
    *p++ = 0x11; /* SGN_ALG */
    *p++ = 0x00;
    if (conf_req_flag) {
	*p++ = 0x10; /* SEAL_ALG */
	*p++ = 0x00;
    } else {
	*p++ = 0xff; /* SEAL_ALG */
	*p++ = 0xff;
    }
    *p++ = 0xff; /* Filler */
    *p++ = 0xff;

    p = NULL;

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    krb5_auth_con_getlocalseqnumber (context,
				     context_handle->auth_context,
				     &seq_number);

    _gsskrb5_encode_be_om_uint32(seq_number, p0 + 8);

    krb5_auth_con_setlocalseqnumber (context,
				     context_handle->auth_context,
				     ++seq_number);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

    memset (p0 + 8 + 4,
	    (context_handle->more_flags & LOCAL) ? 0 : 0xff,
	    4);

    krb5_generate_random_block(p0 + 24, 8); /* fill in Confounder */

    /* p points to data */
    p = p0 + GSS_ARCFOUR_WRAP_TOKEN_SIZE;
    memcpy(p, input_message_buffer->value, input_message_buffer->length);

    if (!IS_DCE_STYLE(context_handle))
	p[input_message_buffer->length] = 1; /* padding */

    ret = arcfour_mic_cksum(context,
			    key, KRB5_KU_USAGE_SEAL,
			    p0 + 16, 8, /* SGN_CKSUM */
			    p0, 8, /* TOK_ID, SGN_ALG, SEAL_ALG, Filler */
			    p0 + 24, 8, /* Confounder */
			    p0 + GSS_ARCFOUR_WRAP_TOKEN_SIZE,
			    datalen);
    if (ret) {
	*minor_status = ret;
	_gsskrb5_release_buffer(minor_status, output_message_buffer);
	return GSS_S_FAILURE;
    }

    {
	int i;

	Klocal.keytype = key->keytype;
	Klocal.keyvalue.data = Klocaldata;
	Klocal.keyvalue.length = sizeof(Klocaldata);

	for (i = 0; i < 16; i++)
	    Klocaldata[i] = ((u_char *)key->keyvalue.data)[i] ^ 0xF0;
    }
    ret = arcfour_mic_key(context, &Klocal,
			  p0 + 8, 4, /* SND_SEQ */
			  k6_data, sizeof(k6_data));
    memset(Klocaldata, 0, sizeof(Klocaldata));
    if (ret) {
	_gsskrb5_release_buffer(minor_status, output_message_buffer);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }


    if(conf_req_flag) {
	EVP_CIPHER_CTX *rc4_key;

	rc4_key = EVP_CIPHER_CTX_new();
	if (rc4_key == NULL) {
	    _gsskrb5_release_buffer(minor_status, output_message_buffer);
	    *minor_status = ENOMEM;
	    return GSS_S_FAILURE;
	}
	EVP_CipherInit_ex(rc4_key, EVP_rc4(), NULL, k6_data, NULL, 1);
	EVP_Cipher(rc4_key, p0 + 24, p0 + 24, 8 + datalen);
	EVP_CIPHER_CTX_free(rc4_key);
    }
    memset(k6_data, 0, sizeof(k6_data));

    ret = arcfour_mic_key(context, key,
			  p0 + 16, 8, /* SGN_CKSUM */
			  k6_data, sizeof(k6_data));
    if (ret) {
	_gsskrb5_release_buffer(minor_status, output_message_buffer);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    {
	EVP_CIPHER_CTX *rc4_key;

	rc4_key = EVP_CIPHER_CTX_new();
	if (rc4_key == NULL) {
	    _gsskrb5_release_buffer(minor_status, output_message_buffer);
	    *minor_status = ENOMEM;
	    return GSS_S_FAILURE;
	}
	EVP_CipherInit_ex(rc4_key, EVP_rc4(), NULL, k6_data, NULL, 1);
	EVP_Cipher(rc4_key, p0 + 8, p0 + 8 /* SND_SEQ */, 8);
	EVP_CIPHER_CTX_free(rc4_key);
	memset(k6_data, 0, sizeof(k6_data));
    }

    if (conf_state)
	*conf_state = conf_req_flag;

    *minor_status = 0;
    return GSS_S_COMPLETE;
}