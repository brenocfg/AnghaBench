#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_object {int dummy; } ;
typedef  int /*<<< orphan*/  modulus_bits ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  CK_ULONG ;
typedef  int /*<<< orphan*/  CK_RV ;
typedef  scalar_t__ CK_KEY_TYPE ;
typedef  int /*<<< orphan*/  CK_BYTE ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 size_t BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CKA_MODULUS ; 
 int /*<<< orphan*/  CKA_MODULUS_BITS ; 
 int /*<<< orphan*/  CKA_PUBLIC_EXPONENT ; 
 scalar_t__ CKK_RSA ; 
 int /*<<< orphan*/  CKR_GENERAL_ERROR ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/ * _hx509_cert_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _hx509_private_key_get_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  add_object_attribute (struct st_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static CK_RV
add_pubkey_info(hx509_context hxctx, struct st_object *o,
		CK_KEY_TYPE key_type, hx509_cert cert)
{
    BIGNUM *num;
    CK_BYTE *modulus = NULL;
    size_t modulus_len = 0;
    CK_ULONG modulus_bits = 0;
    CK_BYTE *exponent = NULL;
    size_t exponent_len = 0;

    if (key_type != CKK_RSA)
	return CKR_OK;
    if (_hx509_cert_private_key(cert) == NULL)
	return CKR_OK;

    num = _hx509_private_key_get_internal(context,
					  _hx509_cert_private_key(cert),
					  "rsa-modulus");
    if (num == NULL)
	return CKR_GENERAL_ERROR;
    modulus_bits = BN_num_bits(num);

    modulus_len = BN_num_bytes(num);
    modulus = malloc(modulus_len);
    BN_bn2bin(num, modulus);
    BN_free(num);

    add_object_attribute(o, 0, CKA_MODULUS, modulus, modulus_len);
    add_object_attribute(o, 0, CKA_MODULUS_BITS,
			 &modulus_bits, sizeof(modulus_bits));

    free(modulus);

    num = _hx509_private_key_get_internal(context,
					  _hx509_cert_private_key(cert),
					  "rsa-exponent");
    if (num == NULL)
	return CKR_GENERAL_ERROR;

    exponent_len = BN_num_bytes(num);
    exponent = malloc(exponent_len);
    BN_bn2bin(num, exponent);
    BN_free(num);

    add_object_attribute(o, 0, CKA_PUBLIC_EXPONENT,
			 exponent, exponent_len);

    free(exponent);

    return CKR_OK;
}