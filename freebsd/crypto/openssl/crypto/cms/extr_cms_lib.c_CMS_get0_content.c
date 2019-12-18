#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {int /*<<< orphan*/ * eContent; } ;
struct TYPE_32__ {TYPE_7__* encryptedContentInfo; } ;
struct TYPE_31__ {int /*<<< orphan*/ * encryptedContent; } ;
struct TYPE_30__ {TYPE_5__* encapContentInfo; } ;
struct TYPE_29__ {int /*<<< orphan*/ * eContent; } ;
struct TYPE_28__ {TYPE_3__* encryptedContentInfo; } ;
struct TYPE_27__ {int /*<<< orphan*/ * encryptedContent; } ;
struct TYPE_26__ {TYPE_1__* encapContentInfo; } ;
struct TYPE_25__ {int /*<<< orphan*/ * eContent; } ;
struct TYPE_23__ {TYPE_14__* other; TYPE_12__* compressedData; TYPE_10__* authenticatedData; TYPE_8__* encryptedData; TYPE_6__* digestedData; TYPE_4__* envelopedData; TYPE_2__* signedData; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {TYPE_15__ d; int /*<<< orphan*/  contentType; } ;
struct TYPE_21__ {int /*<<< orphan*/ * octet_string; } ;
struct TYPE_22__ {TYPE_13__ value; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {TYPE_11__* encapContentInfo; } ;
struct TYPE_19__ {int /*<<< orphan*/ * eContent; } ;
struct TYPE_18__ {TYPE_9__* encapContentInfo; } ;
typedef  TYPE_16__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_GET0_CONTENT ; 
 int /*<<< orphan*/  CMS_R_UNSUPPORTED_CONTENT_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_id_smime_ct_authData 134 
#define  NID_id_smime_ct_compressedData 133 
#define  NID_pkcs7_data 132 
#define  NID_pkcs7_digest 131 
#define  NID_pkcs7_encrypted 130 
#define  NID_pkcs7_enveloped 129 
#define  NID_pkcs7_signed 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 

ASN1_OCTET_STRING **CMS_get0_content(CMS_ContentInfo *cms)
{
    switch (OBJ_obj2nid(cms->contentType)) {

    case NID_pkcs7_data:
        return &cms->d.data;

    case NID_pkcs7_signed:
        return &cms->d.signedData->encapContentInfo->eContent;

    case NID_pkcs7_enveloped:
        return &cms->d.envelopedData->encryptedContentInfo->encryptedContent;

    case NID_pkcs7_digest:
        return &cms->d.digestedData->encapContentInfo->eContent;

    case NID_pkcs7_encrypted:
        return &cms->d.encryptedData->encryptedContentInfo->encryptedContent;

    case NID_id_smime_ct_authData:
        return &cms->d.authenticatedData->encapContentInfo->eContent;

    case NID_id_smime_ct_compressedData:
        return &cms->d.compressedData->encapContentInfo->eContent;

    default:
        if (cms->d.other->type == V_ASN1_OCTET_STRING)
            return &cms->d.other->value.octet_string;
        CMSerr(CMS_F_CMS_GET0_CONTENT, CMS_R_UNSUPPORTED_CONTENT_TYPE);
        return NULL;

    }
}