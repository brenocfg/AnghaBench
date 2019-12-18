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
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_TLC ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_item_ex_free (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int asn1_item_embed_d2i (int /*<<< orphan*/ **,unsigned char const**,long,int /*<<< orphan*/  const*,int,int,char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ASN1_item_ex_d2i(ASN1_VALUE **pval, const unsigned char **in, long len,
                     const ASN1_ITEM *it,
                     int tag, int aclass, char opt, ASN1_TLC *ctx)
{
    int rv;
    rv = asn1_item_embed_d2i(pval, in, len, it, tag, aclass, opt, ctx, 0);
    if (rv <= 0)
        ASN1_item_ex_free(pval, it);
    return rv;
}