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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CMS_F_CMS_SET1_KEYID ; 
 int /*<<< orphan*/  CMS_R_CERTIFICATE_HAS_NO_KEYID ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * X509_get0_subject_key_id (int /*<<< orphan*/ *) ; 

int cms_set1_keyid(ASN1_OCTET_STRING **pkeyid, X509 *cert)
{
    ASN1_OCTET_STRING *keyid = NULL;
    const ASN1_OCTET_STRING *cert_keyid;
    cert_keyid = X509_get0_subject_key_id(cert);
    if (cert_keyid == NULL) {
        CMSerr(CMS_F_CMS_SET1_KEYID, CMS_R_CERTIFICATE_HAS_NO_KEYID);
        return 0;
    }
    keyid = ASN1_STRING_dup(cert_keyid);
    if (!keyid) {
        CMSerr(CMS_F_CMS_SET1_KEYID, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ASN1_OCTET_STRING_free(*pkeyid);
    *pkeyid = keyid;
    return 1;
}