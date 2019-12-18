#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_14__ {int length; char* data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int32_t ;
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  TYPE_4__* gss_buffer_t ;
struct TYPE_13__ {char* data; int length; } ;
struct TYPE_17__ {TYPE_1__ checksum; } ;
struct TYPE_16__ {size_t length; char* value; } ;
struct TYPE_15__ {int more_flags; int /*<<< orphan*/  ctx_id_mutex; int /*<<< orphan*/  auth_context; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  TYPE_5__ Checksum ;

/* Variables and functions */
 int COMPAT_OLD_DES3 ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ETYPE_DES3_CBC_NONE ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SEQ ; 
 int /*<<< orphan*/  KRB5_KU_USAGE_SIGN ; 
 int LOCAL ; 
 int /*<<< orphan*/  _gsskrb5_encap_length (int,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 char* _gsskrb5_make_header (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_Checksum (TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_auth_con_getlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  krb5_auth_con_setlocalseqnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ krb5_create_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 scalar_t__ krb5_encrypt_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_2__*,char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static OM_uint32
mic_des3
           (OM_uint32 * minor_status,
            const gsskrb5_ctx ctx,
	    krb5_context context,
            gss_qop_t qop_req,
            const gss_buffer_t message_buffer,
            gss_buffer_t message_token,
	    krb5_keyblock *key
           )
{
  u_char *p;
  Checksum cksum;
  u_char seq[8];

  int32_t seq_number;
  size_t len, total_len;

  krb5_crypto crypto;
  krb5_error_code kret;
  krb5_data encdata;
  char *tmp;
  char ivec[8];

  _gsskrb5_encap_length (36, &len, &total_len, GSS_KRB5_MECHANISM);

  message_token->length = total_len;
  message_token->value  = malloc (total_len);
  if (message_token->value == NULL) {
      message_token->length = 0;
      *minor_status = ENOMEM;
      return GSS_S_FAILURE;
  }

  p = _gsskrb5_make_header(message_token->value,
			      len,
			      "\x01\x01", /* TOK-ID */
			      GSS_KRB5_MECHANISM);

  memcpy (p, "\x04\x00", 2);	/* SGN_ALG = HMAC SHA1 DES3-KD */
  p += 2;

  memcpy (p, "\xff\xff\xff\xff", 4); /* filler */
  p += 4;

  /* this should be done in parts */

  tmp = malloc (message_buffer->length + 8);
  if (tmp == NULL) {
      free (message_token->value);
      message_token->value = NULL;
      message_token->length = 0;
      *minor_status = ENOMEM;
      return GSS_S_FAILURE;
  }
  memcpy (tmp, p - 8, 8);
  memcpy (tmp + 8, message_buffer->value, message_buffer->length);

  kret = krb5_crypto_init(context, key, 0, &crypto);
  if (kret) {
      free (message_token->value);
      message_token->value = NULL;
      message_token->length = 0;
      free (tmp);
      *minor_status = kret;
      return GSS_S_FAILURE;
  }

  kret = krb5_create_checksum (context,
			       crypto,
			       KRB5_KU_USAGE_SIGN,
			       0,
			       tmp,
			       message_buffer->length + 8,
			       &cksum);
  free (tmp);
  krb5_crypto_destroy (context, crypto);
  if (kret) {
      free (message_token->value);
      message_token->value = NULL;
      message_token->length = 0;
      *minor_status = kret;
      return GSS_S_FAILURE;
  }

  memcpy (p + 8, cksum.checksum.data, cksum.checksum.length);

  HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);
  /* sequence number */
  krb5_auth_con_getlocalseqnumber (context,
			       ctx->auth_context,
			       &seq_number);

  seq[0] = (seq_number >> 0)  & 0xFF;
  seq[1] = (seq_number >> 8)  & 0xFF;
  seq[2] = (seq_number >> 16) & 0xFF;
  seq[3] = (seq_number >> 24) & 0xFF;
  memset (seq + 4,
	  (ctx->more_flags & LOCAL) ? 0 : 0xFF,
	  4);

  kret = krb5_crypto_init(context, key,
			  ETYPE_DES3_CBC_NONE, &crypto);
  if (kret) {
      free (message_token->value);
      message_token->value = NULL;
      message_token->length = 0;
      *minor_status = kret;
      return GSS_S_FAILURE;
  }

  if (ctx->more_flags & COMPAT_OLD_DES3)
      memset(ivec, 0, 8);
  else
      memcpy(ivec, p + 8, 8);

  kret = krb5_encrypt_ivec (context,
			    crypto,
			    KRB5_KU_USAGE_SEQ,
			    seq, 8, &encdata, ivec);
  krb5_crypto_destroy (context, crypto);
  if (kret) {
      free (message_token->value);
      message_token->value = NULL;
      message_token->length = 0;
      *minor_status = kret;
      return GSS_S_FAILURE;
  }

  assert (encdata.length == 8);

  memcpy (p, encdata.data, encdata.length);
  krb5_data_free (&encdata);

  krb5_auth_con_setlocalseqnumber (context,
			       ctx->auth_context,
			       ++seq_number);
  HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

  free_Checksum (&cksum);
  *minor_status = 0;
  return GSS_S_COMPLETE;
}