#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  ivec ;
typedef  int /*<<< orphan*/  hx509_crypto ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;
struct TYPE_30__ {int /*<<< orphan*/  algorithm; TYPE_4__* parameters; } ;
struct TYPE_26__ {TYPE_9__ contentEncryptionAlgorithm; int /*<<< orphan*/  contentType; TYPE_5__* encryptedContent; } ;
struct TYPE_24__ {size_t len; TYPE_7__* val; } ;
struct TYPE_28__ {scalar_t__ length; int /*<<< orphan*/  data; TYPE_3__ encryptedContentInfo; TYPE_1__ recipientInfos; } ;
typedef  TYPE_5__ heim_oid ;
typedef  TYPE_5__ heim_octet_string ;
typedef  int /*<<< orphan*/  ed ;
struct TYPE_25__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_29__ {int /*<<< orphan*/  rid; TYPE_2__ keyEncryptionAlgorithm; int /*<<< orphan*/  encryptedKey; } ;
struct TYPE_27__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ KeyTransRecipientInfo ;
typedef  TYPE_5__ EnvelopedData ;
typedef  TYPE_9__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_CMS_NO_DATA_AVAILABLE ; 
 int HX509_CMS_NO_RECIPIENT_CERTIFICATE ; 
 int HX509_CMS_UE_ALLOW_WEAK ; 
 int HX509_CMS_UE_DONT_REQUIRE_KU_ENCIPHERMENT ; 
 int /*<<< orphan*/  HX509_ERROR_APPEND ; 
 int HX509_QUERY_KU_ENCIPHERMENT ; 
 int HX509_QUERY_PRIVATE_KEY ; 
 int _hx509_cert_private_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int decode_EnvelopedData (void const*,size_t,TYPE_5__*,size_t*) ; 
 int der_copy_oid (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_5__*) ; 
 int /*<<< orphan*/  der_free_oid (TYPE_5__*) ; 
 int find_CMSIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_EnvelopedData (TYPE_5__*) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_crypto_allow_weak (int /*<<< orphan*/ ) ; 
 int hx509_crypto_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  hx509_crypto_destroy (int /*<<< orphan*/ ) ; 
 int hx509_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_crypto_set_key_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int hx509_crypto_set_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int unparse_CMSIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 

int
hx509_cms_unenvelope(hx509_context context,
		     hx509_certs certs,
		     int flags,
		     const void *data,
		     size_t length,
		     const heim_octet_string *encryptedContent,
		     time_t time_now,
		     heim_oid *contentType,
		     heim_octet_string *content)
{
    heim_octet_string key;
    EnvelopedData ed;
    hx509_cert cert;
    AlgorithmIdentifier *ai;
    const heim_octet_string *enccontent;
    heim_octet_string *params, params_data;
    heim_octet_string ivec;
    size_t size;
    int ret, matched = 0, findflags = 0;
    size_t i;


    memset(&key, 0, sizeof(key));
    memset(&ed, 0, sizeof(ed));
    memset(&ivec, 0, sizeof(ivec));
    memset(content, 0, sizeof(*content));
    memset(contentType, 0, sizeof(*contentType));

    if ((flags & HX509_CMS_UE_DONT_REQUIRE_KU_ENCIPHERMENT) == 0)
	findflags |= HX509_QUERY_KU_ENCIPHERMENT;

    ret = decode_EnvelopedData(data, length, &ed, &size);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to decode EnvelopedData");
	return ret;
    }

    if (ed.recipientInfos.len == 0) {
	ret = HX509_CMS_NO_RECIPIENT_CERTIFICATE;
	hx509_set_error_string(context, 0, ret,
			       "No recipient info in enveloped data");
	goto out;
    }

    enccontent = ed.encryptedContentInfo.encryptedContent;
    if (enccontent == NULL) {
	if (encryptedContent == NULL) {
	    ret = HX509_CMS_NO_DATA_AVAILABLE;
	    hx509_set_error_string(context, 0, ret,
				   "Content missing from encrypted data");
	    goto out;
	}
	enccontent = encryptedContent;
    } else if (encryptedContent != NULL) {
	ret = HX509_CMS_NO_DATA_AVAILABLE;
	hx509_set_error_string(context, 0, ret,
			       "Both internal and external encrypted data");
	goto out;
    }

    cert = NULL;
    for (i = 0; i < ed.recipientInfos.len; i++) {
	KeyTransRecipientInfo *ri;
	char *str;
	int ret2;

	ri = &ed.recipientInfos.val[i];

	ret = find_CMSIdentifier(context, &ri->rid, certs,
				 time_now, &cert,
				 HX509_QUERY_PRIVATE_KEY|findflags);
	if (ret)
	    continue;

	matched = 1; /* found a matching certificate, let decrypt */

	ret = _hx509_cert_private_decrypt(context,
					  &ri->encryptedKey,
					  &ri->keyEncryptionAlgorithm.algorithm,
					  cert, &key);

	hx509_cert_free(cert);
	if (ret == 0)
	    break; /* succuessfully decrypted cert */
	cert = NULL;
	ret2 = unparse_CMSIdentifier(context, &ri->rid, &str);
	if (ret2 == 0) {
	    hx509_set_error_string(context, HX509_ERROR_APPEND, ret,
				   "Failed to decrypt with %s", str);
	    free(str);
	}
    }

    if (!matched) {
	ret = HX509_CMS_NO_RECIPIENT_CERTIFICATE;
	hx509_set_error_string(context, 0, ret,
			       "No private key matched any certificate");
	goto out;
    }

    if (cert == NULL) {
	ret = HX509_CMS_NO_RECIPIENT_CERTIFICATE;
	hx509_set_error_string(context, HX509_ERROR_APPEND, ret,
			       "No private key decrypted the transfer key");
	goto out;
    }

    ret = der_copy_oid(&ed.encryptedContentInfo.contentType, contentType);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to copy EnvelopedData content oid");
	goto out;
    }

    ai = &ed.encryptedContentInfo.contentEncryptionAlgorithm;
    if (ai->parameters) {
	params_data.data = ai->parameters->data;
	params_data.length = ai->parameters->length;
	params = &params_data;
    } else
	params = NULL;

    {
	hx509_crypto crypto;

	ret = hx509_crypto_init(context, NULL, &ai->algorithm, &crypto);
	if (ret)
	    goto out;

	if (flags & HX509_CMS_UE_ALLOW_WEAK)
	    hx509_crypto_allow_weak(crypto);

	if (params) {
	    ret = hx509_crypto_set_params(context, crypto, params, &ivec);
	    if (ret) {
		hx509_crypto_destroy(crypto);
		goto out;
	    }
	}

	ret = hx509_crypto_set_key_data(crypto, key.data, key.length);
	if (ret) {
	    hx509_crypto_destroy(crypto);
	    hx509_set_error_string(context, 0, ret,
				   "Failed to set key for decryption "
				   "of EnvelopedData");
	    goto out;
	}

	ret = hx509_crypto_decrypt(crypto,
				   enccontent->data,
				   enccontent->length,
				   ivec.length ? &ivec : NULL,
				   content);
	hx509_crypto_destroy(crypto);
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to decrypt EnvelopedData");
	    goto out;
	}
    }

out:

    free_EnvelopedData(&ed);
    der_free_octet_string(&key);
    if (ivec.length)
	der_free_octet_string(&ivec);
    if (ret) {
	der_free_oid(contentType);
	der_free_octet_string(content);
    }

    return ret;
}