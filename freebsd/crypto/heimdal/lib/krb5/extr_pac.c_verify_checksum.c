#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct PAC_INFO_BUFFER {int offset_lo; scalar_t__ buffersize; } ;
typedef  int /*<<< orphan*/  local_checksum ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int krb5_error_code ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/ * krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  cksum ;
struct TYPE_12__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_11__ {scalar_t__ cksumtype; TYPE_6__ checksum; } ;
typedef  TYPE_2__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CKSUMTYPE_HMAC_MD5 ; 
 int EINVAL ; 
 int HMAC_MD5_any_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int KRB5KRB_AP_ERR_BAD_INTEGRITY ; 
 int /*<<< orphan*/  KRB5_KU_OTHER_CKSUM ; 
 int /*<<< orphan*/  KRB5_STORAGE_BYTEORDER_LE ; 
 char* N_ (char*,char*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_checksum_is_keyed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_data_ct_cmp (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_6__*) ; 
 int krb5_enomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (char*,scalar_t__) ; 
 int krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_verify_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static krb5_error_code
verify_checksum(krb5_context context,
		const struct PAC_INFO_BUFFER *sig,
		const krb5_data *data,
		void *ptr, size_t len,
		const krb5_keyblock *key)
{
    krb5_storage *sp = NULL;
    uint32_t type;
    krb5_error_code ret;
    Checksum cksum;

    memset(&cksum, 0, sizeof(cksum));

    sp = krb5_storage_from_mem((char *)data->data + sig->offset_lo,
			       sig->buffersize);
    if (sp == NULL)
	return krb5_enomem(context);

    krb5_storage_set_flags(sp, KRB5_STORAGE_BYTEORDER_LE);

    CHECK(ret, krb5_ret_uint32(sp, &type), out);
    cksum.cksumtype = type;
    cksum.checksum.length =
	sig->buffersize - krb5_storage_seek(sp, 0, SEEK_CUR);
    cksum.checksum.data = malloc(cksum.checksum.length);
    if (cksum.checksum.data == NULL) {
	ret = krb5_enomem(context);
	goto out;
    }
    ret = krb5_storage_read(sp, cksum.checksum.data, cksum.checksum.length);
    if (ret != (int)cksum.checksum.length) {
	ret = EINVAL;
	krb5_set_error_message(context, ret, "PAC checksum missing checksum");
	goto out;
    }

    if (!krb5_checksum_is_keyed(context, cksum.cksumtype)) {
	ret = EINVAL;
	krb5_set_error_message(context, ret, "Checksum type %d not keyed",
			       cksum.cksumtype);
	goto out;
    }

    /* If the checksum is HMAC-MD5, the checksum type is not tied to
     * the key type, instead the HMAC-MD5 checksum is applied blindly
     * on whatever key is used for this connection, avoiding issues
     * with unkeyed checksums on des-cbc-md5 and des-cbc-crc.  See
     * http://comments.gmane.org/gmane.comp.encryption.kerberos.devel/8743
     * for the same issue in MIT, and
     * http://blogs.msdn.com/b/openspecification/archive/2010/01/01/verifying-the-server-signature-in-kerberos-privilege-account-certificate.aspx
     * for Microsoft's explaination */

    if (cksum.cksumtype == CKSUMTYPE_HMAC_MD5) {
	Checksum local_checksum;

	memset(&local_checksum, 0, sizeof(local_checksum));

	ret = HMAC_MD5_any_checksum(context, key, ptr, len,
				    KRB5_KU_OTHER_CKSUM, &local_checksum);

	if (ret != 0 || krb5_data_ct_cmp(&local_checksum.checksum, &cksum.checksum) != 0) {
	    ret = KRB5KRB_AP_ERR_BAD_INTEGRITY;
	    krb5_set_error_message(context, ret,
				   N_("PAC integrity check failed for "
				      "hmac-md5 checksum", ""));
	}
	krb5_data_free(&local_checksum.checksum);

   } else {
	krb5_crypto crypto = NULL;

	ret = krb5_crypto_init(context, key, 0, &crypto);
	if (ret)
		goto out;

	ret = krb5_verify_checksum(context, crypto, KRB5_KU_OTHER_CKSUM,
				   ptr, len, &cksum);
	krb5_crypto_destroy(context, crypto);
    }
    free(cksum.checksum.data);
    krb5_storage_free(sp);

    return ret;

out:
    if (cksum.checksum.data)
	free(cksum.checksum.data);
    if (sp)
	krb5_storage_free(sp);
    return ret;
}