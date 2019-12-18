#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_TLC ;
typedef  TYPE_1__ ASN1_TEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_TEMPLATE_EX_D2I ; 
 int /*<<< orphan*/  ASN1_R_EXPLICIT_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  ASN1_R_EXPLICIT_TAG_NOT_CONSTRUCTED ; 
 int /*<<< orphan*/  ASN1_R_MISSING_EOC ; 
 int ASN1_TFLG_EXPTAG ; 
 int ASN1_TFLG_TAG_CLASS ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_NESTED_ASN1_ERROR ; 
 int /*<<< orphan*/  asn1_check_eoc (unsigned char const**,long) ; 
 int asn1_check_tlen (long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,unsigned char const**,long,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ *) ; 
 int asn1_template_noexp_d2i (int /*<<< orphan*/ **,unsigned char const**,long,TYPE_1__ const*,char,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int asn1_template_ex_d2i(ASN1_VALUE **val,
                                const unsigned char **in, long inlen,
                                const ASN1_TEMPLATE *tt, char opt,
                                ASN1_TLC *ctx, int depth)
{
    int flags, aclass;
    int ret;
    long len;
    const unsigned char *p, *q;
    char exp_eoc;
    if (!val)
        return 0;
    flags = tt->flags;
    aclass = flags & ASN1_TFLG_TAG_CLASS;

    p = *in;

    /* Check if EXPLICIT tag expected */
    if (flags & ASN1_TFLG_EXPTAG) {
        char cst;
        /*
         * Need to work out amount of data available to the inner content and
         * where it starts: so read in EXPLICIT header to get the info.
         */
        ret = asn1_check_tlen(&len, NULL, NULL, &exp_eoc, &cst,
                              &p, inlen, tt->tag, aclass, opt, ctx);
        q = p;
        if (!ret) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        } else if (ret == -1)
            return -1;
        if (!cst) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I,
                    ASN1_R_EXPLICIT_TAG_NOT_CONSTRUCTED);
            return 0;
        }
        /* We've found the field so it can't be OPTIONAL now */
        ret = asn1_template_noexp_d2i(val, &p, len, tt, 0, ctx, depth);
        if (!ret) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        }
        /* We read the field in OK so update length */
        len -= p - q;
        if (exp_eoc) {
            /* If NDEF we must have an EOC here */
            if (!asn1_check_eoc(&p, len)) {
                ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ASN1_R_MISSING_EOC);
                goto err;
            }
        } else {
            /*
             * Otherwise we must hit the EXPLICIT tag end or its an error
             */
            if (len) {
                ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I,
                        ASN1_R_EXPLICIT_LENGTH_MISMATCH);
                goto err;
            }
        }
    } else
        return asn1_template_noexp_d2i(val, in, inlen, tt, opt, ctx, depth);

    *in = p;
    return 1;

 err:
    return 0;
}