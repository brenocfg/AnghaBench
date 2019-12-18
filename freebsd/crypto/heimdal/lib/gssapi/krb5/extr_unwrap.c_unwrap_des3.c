#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
struct TYPE_16__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_15__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {TYPE_1__ checksum; int /*<<< orphan*/  cksumtype; } ;
struct TYPE_18__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_17__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  order; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  DES_cblock ;
typedef  TYPE_5__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_HMAC_SHA1_DES3 ; 
 int /*<<< orphan*/  ETYPE_DES3_CBC_NONE ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_BAD_MIC ; 
 scalar_t__ GSS_S_BAD_SIG ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_DCE_STYLE (TYPE_3__* const) ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SEAL ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SEQ ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SIGN ; 
 int LOCAL ; 
 scalar_t__ _gssapi_msg_order_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _gssapi_verify_pad (TYPE_4__* const,size_t,size_t*) ; 
 int /*<<< orphan*/  _gsskrb5_decode_om_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _gsskrb5_verify_header (int /*<<< orphan*/ **,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ct_memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 scalar_t__ krb5_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,TYPE_2__*) ; 
 scalar_t__ krb5_decrypt_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_verify_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,TYPE_5__*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static OM_uint32
unwrap_des3
           (OM_uint32 * minor_status,
            const gsskrb5_ctx context_handle,
	    krb5_context context,
            const gss_buffer_t input_message_buffer,
            gss_buffer_t output_message_buffer,
            int * conf_state,
            gss_qop_t * qop_state,
	    krb5_keyblock *key
           )
{
  u_char *p;
  size_t len;
  u_char *seq;
  krb5_data seq_data;
  u_char cksum[20];
  uint32_t seq_number;
  size_t padlength;
  OM_uint32 ret;
  int cstate;
  krb5_crypto crypto;
  Checksum csum;
  int cmp;
  int token_len;

  if (IS_DCE_STYLE(context_handle)) {
     token_len = 34 + 8 + 15; /* 57 */
  } else {
     token_len = input_message_buffer->length;
  }

  p = input_message_buffer->value;
  ret = _gsskrb5_verify_header (&p,
				   token_len,
				   "\x02\x01",
				   GSS_KRB5_MECHANISM);
  if (ret)
      return ret;

  if (memcmp (p, "\x04\x00", 2) != 0) /* HMAC SHA1 DES3_KD */
    return GSS_S_BAD_SIG;
  p += 2;
  if (ct_memcmp (p, "\x02\x00", 2) == 0) {
    cstate = 1;
  } else if (ct_memcmp (p, "\xff\xff", 2) == 0) {
    cstate = 0;
  } else
    return GSS_S_BAD_MIC;
  p += 2;
  if(conf_state != NULL)
    *conf_state = cstate;
  if (ct_memcmp (p, "\xff\xff", 2) != 0)
    return GSS_S_DEFECTIVE_TOKEN;
  p += 2;
  p += 28;

  len = p - (u_char *)input_message_buffer->value;

  if(cstate) {
      /* decrypt data */
      krb5_data tmp;

      ret = krb5_crypto_init(context, key,
			     ETYPE_DES3_CBC_NONE, &crypto);
      if (ret) {
	  *minor_status = ret;
	  return GSS_S_FAILURE;
      }
      ret = krb5_decrypt(context, crypto, KRB5_KU_USAGE_SEAL,
			 p, input_message_buffer->length - len, &tmp);
      krb5_crypto_destroy(context, crypto);
      if (ret) {
	  *minor_status = ret;
	  return GSS_S_FAILURE;
      }
      assert (tmp.length == input_message_buffer->length - len);

      memcpy (p, tmp.data, tmp.length);
      krb5_data_free(&tmp);
  }

  if (IS_DCE_STYLE(context_handle)) {
    padlength = 0;
  } else {
    /* check pad */
    ret = _gssapi_verify_pad(input_message_buffer,
			     input_message_buffer->length - len,
			     &padlength);
    if (ret)
        return ret;
  }

  /* verify sequence number */

  HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);

  p -= 28;

  ret = krb5_crypto_init(context, key,
			 ETYPE_DES3_CBC_NONE, &crypto);
  if (ret) {
      *minor_status = ret;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_FAILURE;
  }
  {
      DES_cblock ivec;

      memcpy(&ivec, p + 8, 8);
      ret = krb5_decrypt_ivec (context,
			       crypto,
			       KRB5_KU_USAGE_SEQ,
			       p, 8, &seq_data,
			       &ivec);
  }
  krb5_crypto_destroy (context, crypto);
  if (ret) {
      *minor_status = ret;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_FAILURE;
  }
  if (seq_data.length != 8) {
      krb5_data_free (&seq_data);
      *minor_status = 0;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_BAD_MIC;
  }

  seq = seq_data.data;
  _gsskrb5_decode_om_uint32(seq, &seq_number);

  if (context_handle->more_flags & LOCAL)
      cmp = ct_memcmp(&seq[4], "\xff\xff\xff\xff", 4);
  else
      cmp = ct_memcmp(&seq[4], "\x00\x00\x00\x00", 4);

  krb5_data_free (&seq_data);
  if (cmp != 0) {
      *minor_status = 0;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return GSS_S_BAD_MIC;
  }

  ret = _gssapi_msg_order_check(context_handle->order, seq_number);
  if (ret) {
      *minor_status = 0;
      HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
      return ret;
  }

  HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

  /* verify checksum */

  memcpy (cksum, p + 8, 20);

  memcpy (p + 20, p - 8, 8);

  csum.cksumtype = CKSUMTYPE_HMAC_SHA1_DES3;
  csum.checksum.length = 20;
  csum.checksum.data   = cksum;

  ret = krb5_crypto_init(context, key, 0, &crypto);
  if (ret) {
      *minor_status = ret;
      return GSS_S_FAILURE;
  }

  ret = krb5_verify_checksum (context, crypto,
			      KRB5_KU_USAGE_SIGN,
			      p + 20,
			      input_message_buffer->length - len + 8,
			      &csum);
  krb5_crypto_destroy (context, crypto);
  if (ret) {
      *minor_status = ret;
      return GSS_S_FAILURE;
  }

  /* copy out data */

  output_message_buffer->length = input_message_buffer->length
    - len - padlength - 8;
  output_message_buffer->value  = malloc(output_message_buffer->length);
  if(output_message_buffer->length != 0 && output_message_buffer->value == NULL)
      return GSS_S_FAILURE;
  memcpy (output_message_buffer->value,
	  p + 36,
	  output_message_buffer->length);
  return GSS_S_COMPLETE;
}