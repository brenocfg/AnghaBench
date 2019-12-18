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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bn_print(BIO *out, ASN1_VALUE **pval, const ASN1_ITEM *it,
                    int indent, const ASN1_PCTX *pctx)
{
    if (!BN_print(out, *(BIGNUM **)pval))
        return 0;
    if (BIO_puts(out, "\n") <= 0)
        return 0;
    return 1;
}