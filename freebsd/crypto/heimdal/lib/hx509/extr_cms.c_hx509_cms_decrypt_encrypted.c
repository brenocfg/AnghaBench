#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_12__ {scalar_t__ data; } ;
typedef  TYPE_2__ heim_octet_string ;
typedef  int /*<<< orphan*/  cont ;
struct TYPE_14__ {int /*<<< orphan*/ * parameters; } ;
struct TYPE_11__ {int /*<<< orphan*/ * encryptedContent; TYPE_4__ contentEncryptionAlgorithm; int /*<<< orphan*/  contentType; } ;
struct TYPE_13__ {TYPE_1__ encryptedContentInfo; } ;
typedef  TYPE_3__ CMSEncryptedData ;
typedef  TYPE_4__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_ALG_NOT_SUPP ; 
 int HX509_CMS_NO_DATA_AVAILABLE ; 
 int _hx509_pbe_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int decode_CMSEncryptedData (void const*,size_t,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int der_copy_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_CMSEncryptedData (TYPE_3__*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int
hx509_cms_decrypt_encrypted(hx509_context context,
			    hx509_lock lock,
			    const void *data,
			    size_t length,
			    heim_oid *contentType,
			    heim_octet_string *content)
{
    heim_octet_string cont;
    CMSEncryptedData ed;
    AlgorithmIdentifier *ai;
    int ret;

    memset(content, 0, sizeof(*content));
    memset(&cont, 0, sizeof(cont));

    ret = decode_CMSEncryptedData(data, length, &ed, NULL);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to decode CMSEncryptedData");
	return ret;
    }

    if (ed.encryptedContentInfo.encryptedContent == NULL) {
	ret = HX509_CMS_NO_DATA_AVAILABLE;
	hx509_set_error_string(context, 0, ret,
			       "No content in EncryptedData");
	goto out;
    }

    ret = der_copy_oid(&ed.encryptedContentInfo.contentType, contentType);
    if (ret) {
	hx509_clear_error_string(context);
	goto out;
    }

    ai = &ed.encryptedContentInfo.contentEncryptionAlgorithm;
    if (ai->parameters == NULL) {
	ret = HX509_ALG_NOT_SUPP;
	hx509_clear_error_string(context);
	goto out;
    }

    ret = _hx509_pbe_decrypt(context,
			     lock,
			     ai,
			     ed.encryptedContentInfo.encryptedContent,
			     &cont);
    if (ret)
	goto out;

    *content = cont;

out:
    if (ret) {
	if (cont.data)
	    free(cont.data);
    }
    free_CMSEncryptedData(&ed);
    return ret;
}