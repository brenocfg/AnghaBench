#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* signedData; } ;
struct TYPE_9__ {TYPE_3__ d; } ;
struct TYPE_7__ {TYPE_1__* encapContentInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/ * eContentType; } ;
typedef  int /*<<< orphan*/  CMS_SignerInfo ;
typedef  TYPE_4__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ CMS_signed_add1_attr_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NID_pkcs9_contentType ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 

__attribute__((used)) static int cms_set_si_contentType_attr(CMS_ContentInfo *cms, CMS_SignerInfo *si)
{
    ASN1_OBJECT *ctype = cms->d.signedData->encapContentInfo->eContentType;

    /* Add the contentType attribute */
    return CMS_signed_add1_attr_by_NID(si, NID_pkcs9_contentType,
                                       V_ASN1_OBJECT, ctype, -1) > 0;
}