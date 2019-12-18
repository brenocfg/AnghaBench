#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_6__ {int /*<<< orphan*/ * subjectKeyIdentifier; TYPE_1__* issuerAndSerialNumber; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_5__ {int /*<<< orphan*/ * serialNumber; int /*<<< orphan*/ * issuer; } ;
typedef  TYPE_3__ CMS_SignerIdentifier ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 scalar_t__ CMS_SIGNERINFO_ISSUER_SERIAL ; 
 scalar_t__ CMS_SIGNERINFO_KEYIDENTIFIER ; 

int cms_SignerIdentifier_get0_signer_id(CMS_SignerIdentifier *sid,
                                        ASN1_OCTET_STRING **keyid,
                                        X509_NAME **issuer,
                                        ASN1_INTEGER **sno)
{
    if (sid->type == CMS_SIGNERINFO_ISSUER_SERIAL) {
        if (issuer)
            *issuer = sid->d.issuerAndSerialNumber->issuer;
        if (sno)
            *sno = sid->d.issuerAndSerialNumber->serialNumber;
    } else if (sid->type == CMS_SIGNERINFO_KEYIDENTIFIER) {
        if (keyid)
            *keyid = sid->d.subjectKeyIdentifier;
    } else
        return 0;
    return 1;
}