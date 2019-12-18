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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_cksumtype ;

/* Variables and functions */
 scalar_t__ CKSUMTYPE_HMAC_MD5 ; 
 scalar_t__ FALSE ; 
 scalar_t__ krb5_checksum_is_keyed (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_checksumsize (int /*<<< orphan*/ ,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_crypto_get_checksum_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
pac_checksum(krb5_context context,
	     const krb5_keyblock *key,
	     uint32_t *cksumtype,
	     size_t *cksumsize)
{
    krb5_cksumtype cktype;
    krb5_error_code ret;
    krb5_crypto crypto = NULL;

    ret = krb5_crypto_init(context, key, 0, &crypto);
    if (ret)
	return ret;

    ret = krb5_crypto_get_checksum_type(context, crypto, &cktype);
    krb5_crypto_destroy(context, crypto);
    if (ret)
	return ret;

    if (krb5_checksum_is_keyed(context, cktype) == FALSE) {
	*cksumtype = CKSUMTYPE_HMAC_MD5;
	*cksumsize = 16;
    }

    ret = krb5_checksumsize(context, cktype, cksumsize);
    if (ret)
	return ret;

    *cksumtype = (uint32_t)cktype;

    return 0;
}