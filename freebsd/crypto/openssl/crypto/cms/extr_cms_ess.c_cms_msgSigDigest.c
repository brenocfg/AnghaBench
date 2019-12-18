#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  signedAttrs; TYPE_1__* digestAlgorithm; } ;
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_2__ CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_item_digest (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  CMS_Attributes_Verify ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cms_msgSigDigest(CMS_SignerInfo *si,
                            unsigned char *dig, unsigned int *diglen)
{
    const EVP_MD *md;
    md = EVP_get_digestbyobj(si->digestAlgorithm->algorithm);
    if (md == NULL)
        return 0;
    if (!ASN1_item_digest(ASN1_ITEM_rptr(CMS_Attributes_Verify), md,
                          si->signedAttrs, dig, diglen))
        return 0;
    return 1;
}