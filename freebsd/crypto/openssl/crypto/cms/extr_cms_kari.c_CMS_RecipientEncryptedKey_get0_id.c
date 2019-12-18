#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {TYPE_2__* rKeyId; TYPE_1__* issuerAndSerialNumber; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__ d; } ;
struct TYPE_10__ {TYPE_5__* rid; } ;
struct TYPE_8__ {int /*<<< orphan*/ * other; int /*<<< orphan*/ * date; int /*<<< orphan*/ * subjectKeyIdentifier; } ;
struct TYPE_7__ {int /*<<< orphan*/ * serialNumber; int /*<<< orphan*/ * issuer; } ;
typedef  TYPE_4__ CMS_RecipientEncryptedKey ;
typedef  int /*<<< orphan*/  CMS_OtherKeyAttribute ;
typedef  TYPE_5__ CMS_KeyAgreeRecipientIdentifier ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 scalar_t__ CMS_REK_ISSUER_SERIAL ; 
 scalar_t__ CMS_REK_KEYIDENTIFIER ; 

int CMS_RecipientEncryptedKey_get0_id(CMS_RecipientEncryptedKey *rek,
                                      ASN1_OCTET_STRING **keyid,
                                      ASN1_GENERALIZEDTIME **tm,
                                      CMS_OtherKeyAttribute **other,
                                      X509_NAME **issuer, ASN1_INTEGER **sno)
{
    CMS_KeyAgreeRecipientIdentifier *rid = rek->rid;
    if (rid->type == CMS_REK_ISSUER_SERIAL) {
        if (issuer)
            *issuer = rid->d.issuerAndSerialNumber->issuer;
        if (sno)
            *sno = rid->d.issuerAndSerialNumber->serialNumber;
        if (keyid)
            *keyid = NULL;
        if (tm)
            *tm = NULL;
        if (other)
            *other = NULL;
    } else if (rid->type == CMS_REK_KEYIDENTIFIER) {
        if (keyid)
            *keyid = rid->d.rKeyId->subjectKeyIdentifier;
        if (tm)
            *tm = rid->d.rKeyId->date;
        if (other)
            *other = rid->d.rKeyId->other;
        if (issuer)
            *issuer = NULL;
        if (sno)
            *sno = NULL;
    } else
        return 0;
    return 1;
}