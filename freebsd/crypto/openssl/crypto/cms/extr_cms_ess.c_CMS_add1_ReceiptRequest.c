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
typedef  int /*<<< orphan*/  CMS_SignerInfo ;
typedef  int /*<<< orphan*/  CMS_ReceiptRequest ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_ADD1_RECEIPTREQUEST ; 
 int /*<<< orphan*/  CMS_signed_add1_attr_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_id_smime_aa_receiptRequest ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_CMS_ReceiptRequest (int /*<<< orphan*/ *,unsigned char**) ; 

int CMS_add1_ReceiptRequest(CMS_SignerInfo *si, CMS_ReceiptRequest *rr)
{
    unsigned char *rrder = NULL;
    int rrderlen, r = 0;

    rrderlen = i2d_CMS_ReceiptRequest(rr, &rrder);
    if (rrderlen < 0)
        goto merr;

    if (!CMS_signed_add1_attr_by_NID(si, NID_id_smime_aa_receiptRequest,
                                     V_ASN1_SEQUENCE, rrder, rrderlen))
        goto merr;

    r = 1;

 merr:
    if (!r)
        CMSerr(CMS_F_CMS_ADD1_RECEIPTREQUEST, ERR_R_MALLOC_FAILURE);

    OPENSSL_free(rrder);

    return r;

}