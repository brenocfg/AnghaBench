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
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int BIO_printf (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  COPY_SIZE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  memcpy (long*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int long_print(BIO *out, ASN1_VALUE **pval, const ASN1_ITEM *it,
                      int indent, const ASN1_PCTX *pctx)
{
    long l;

    memcpy(&l, pval, COPY_SIZE(*pval, l));
    return BIO_printf(out, "%ld\n", l);
}