#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
struct TYPE_13__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_12__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_1__ checksum; int /*<<< orphan*/  cksumtype; } ;
struct TYPE_15__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_14__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  order; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  TYPE_5__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_HMAC_SHA1_DES3 ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ETYPE_DES3_CBC_NONE ; 
 int /*<<< orphan*/  ETYPE_DES3_CBC_SHA1 ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_BAD_MIC ; 
 scalar_t__ GSS_S_BAD_SIG ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SEQ ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SIGN ; 
 int LOCAL ; 
 scalar_t__ _gssapi_msg_order_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_decode_om_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _gsskrb5_verify_header (int /*<<< orphan*/ **,int,char const*,int /*<<< orphan*/ ) ; 
 int ct_memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 scalar_t__ krb5_decrypt_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*,char*) ; 
 scalar_t__ krb5_verify_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_5__*) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OM_uint32
verify_mic_des3
           (OM_uint32 * minor_status,
            const gsskrb5_ctx context_handle,
	    krb5_context context,
            const gss_buffer_t message_buffer,
            const gss_buffer_t token_buffer,
            gss_qop_t * qop_state,
	    krb5_keyblock *key,
	    const char *type
	    )
{
  u_char *p;
  u_char *seq;
  uint32_t seq_number;
  OM_uint32 ret;
  krb5_crypto crypto;
  krb5_data seq_data;
  int cmp, docompat;
  Checksum csum;
  char *tmp;
  char ivec[8];

  p = token_buffer->value;
  ret = _gsskrb5_verify_header (&p,
				   token_buffer->length,
				   type,
				   GSS_KRB5_MECHANISM);
  if (ret)
      return ret;

  if (memcmp(p, "\x04\x00", 2) != 0) /* SGN_ALG = HMAC SHA1 DES3-KD */
      return GSS_S_BAD_SIG;
  p += 2;
  if (memcmp (p, "\xff\xff\xff\xff", 4) != 0)
    return GSS_S_BAD_MIC;
  p += 4;

  ret = krb5_crypto_init(context, key,
			 ETYPE_DES3_CBC_NONE, &crypto);
  if (ret){
      *minor_status = ret;
      return GSS_S_FAILURE;
  }

  /* verify sequence number */
  docompat = 0;
retry:
  if (docompat)
      memset(ivec, 0, 8);
  else
      memcpy(ivec, p + 8, 8);

  ret = krb5_decrypt_ivec (context,
			   crypto,
			   KRB5_KU_USAGE_SEQ,
			   p, 8, &seq_data, ivec);
  if (ret) {
      if (docompat++) {
	  krb5_crypto_destroy (context, crypto);
	  *minor_status = ret;
	  return GSS_S_FAILURE;
      } else
	  goto retry;
  }

  if (seq_data.length != 8) {
      krb5_data_free (&seq_data);
      if (docompat++) {
	  krb5_crypto_destroy (context, crypto);
	  return GSS_S_BAD_MIC;
      } else
	  goto retry;
  }

  HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);

  seq = seq_data.data;
  _gsskrb5_decode_om_uint32(seq, &seq_number);

  if (context_handle->more_flags & LOCAL)
      cmp = ct_memcmp(&seq[4], "\xff\xff\xff\xff", 4);
  else
      cmp = ct_memcmp(&seq[4], "\x00\x00\x00\x00", 4);

  krb5_data_free (&seq_data);
  if (cmp != 0) {
      krb5_crypto_destroy (context, crypto);
      *minor_status = 0;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_BAD_MIC;
  }

  ret = _gssapi_msg_order_check(context_handle->order, seq_number);
  if (ret) {
      krb5_crypto_destroy (context, crypto);
      *minor_status = 0;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return ret;
  }

  /* verify checksum */

  tmp = malloc (message_buffer->length + 8);
  if (tmp == NULL) {
      krb5_crypto_destroy (context, crypto);
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      *minor_status = ENOMEM;
      return GSS_S_FAILURE;
  }

  memcpy (tmp, p - 8, 8);
  memcpy (tmp + 8, message_buffer->value, message_buffer->length);

  csum.cksumtype = CKSUMTYPE_HMAC_SHA1_DES3;
  csum.checksum.length = 20;
  csum.checksum.data   = p + 8;

  krb5_crypto_destroy (context, crypto);
  ret = krb5_crypto_init(context, key,
			 ETYPE_DES3_CBC_SHA1, &crypto);
  if (ret){
      *minor_status = ret;
      return GSS_S_FAILURE;
  }

  ret = krb5_verify_checksum (context, crypto,
			      KRB5_KU_USAGE_SIGN,
			      tmp, message_buffer->length + 8,
			      &csum);
  free (tmp);
  if (ret) {
      krb5_crypto_destroy (context, crypto);
      *minor_status = ret;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_BAD_MIC;
  }
  HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

  krb5_crypto_destroy (context, crypto);
  return GSS_S_COMPLETE;
}