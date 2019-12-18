#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ checksum; } ;
typedef  TYPE_2__ Checksum ;

/* Variables and functions */
 scalar_t__ CKSUMTYPE_HMAC_MD5 ; 
 scalar_t__ EINVAL ; 
 scalar_t__ HMAC_MD5_any_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  KRB5_KU_OTHER_CKSUM ; 
 int /*<<< orphan*/  free_Checksum (TYPE_2__*) ; 
 scalar_t__ krb5_create_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static krb5_error_code
create_checksum(krb5_context context,
		const krb5_keyblock *key,
		uint32_t cksumtype,
		void *data, size_t datalen,
		void *sig, size_t siglen)
{
    krb5_crypto crypto = NULL;
    krb5_error_code ret;
    Checksum cksum;

    /* If the checksum is HMAC-MD5, the checksum type is not tied to
     * the key type, instead the HMAC-MD5 checksum is applied blindly
     * on whatever key is used for this connection, avoiding issues
     * with unkeyed checksums on des-cbc-md5 and des-cbc-crc.  See
     * http://comments.gmane.org/gmane.comp.encryption.kerberos.devel/8743
     * for the same issue in MIT, and
     * http://blogs.msdn.com/b/openspecification/archive/2010/01/01/verifying-the-server-signature-in-kerberos-privilege-account-certificate.aspx
     * for Microsoft's explaination */

    if (cksumtype == (uint32_t)CKSUMTYPE_HMAC_MD5) {
	ret = HMAC_MD5_any_checksum(context, key, data, datalen,
				    KRB5_KU_OTHER_CKSUM, &cksum);
    } else {
	ret = krb5_crypto_init(context, key, 0, &crypto);
	if (ret)
	    return ret;

	ret = krb5_create_checksum(context, crypto, KRB5_KU_OTHER_CKSUM, 0,
				   data, datalen, &cksum);
	krb5_crypto_destroy(context, crypto);
	if (ret)
	    return ret;
    }
    if (cksum.checksum.length != siglen) {
	krb5_set_error_message(context, EINVAL, "pac checksum wrong length");
	free_Checksum(&cksum);
	return EINVAL;
    }

    memcpy(sig, cksum.checksum.data, siglen);
    free_Checksum(&cksum);

    return 0;
}