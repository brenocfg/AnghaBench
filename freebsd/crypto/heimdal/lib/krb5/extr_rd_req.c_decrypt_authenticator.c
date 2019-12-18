#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_key_usage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  EncryptionKey ;
typedef  int /*<<< orphan*/  EncryptedData ;
typedef  int /*<<< orphan*/  Authenticator ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_KU_AP_REQ_AUTH ; 
 int /*<<< orphan*/  KRB5_KU_TGS_REQ_AUTH ; 
 scalar_t__ decode_Authenticator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 scalar_t__ krb5_decrypt_EncryptedData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static krb5_error_code
decrypt_authenticator (krb5_context context,
		       EncryptionKey *key,
		       EncryptedData *enc_part,
		       Authenticator *authenticator,
		       krb5_key_usage usage)
{
    krb5_error_code ret;
    krb5_data plain;
    size_t len;
    krb5_crypto crypto;

    ret = krb5_crypto_init(context, key, 0, &crypto);
    if (ret)
	return ret;
    ret = krb5_decrypt_EncryptedData (context,
				      crypto,
				      usage /* KRB5_KU_AP_REQ_AUTH */,
				      enc_part,
				      &plain);
    /* for backwards compatibility, also try the old usage */
    if (ret && usage == KRB5_KU_TGS_REQ_AUTH)
	ret = krb5_decrypt_EncryptedData (context,
					  crypto,
					  KRB5_KU_AP_REQ_AUTH,
					  enc_part,
					  &plain);
    krb5_crypto_destroy(context, crypto);
    if (ret)
	return ret;

    ret = decode_Authenticator(plain.data, plain.length,
			       authenticator, &len);
    krb5_data_free (&plain);
    return ret;
}