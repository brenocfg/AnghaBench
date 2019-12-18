#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/  nm_flags; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_PCTX ;

/* Variables and functions */
 scalar_t__ X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x509_name_ex_print(BIO *out, ASN1_VALUE **pval,
                              int indent,
                              const char *fname, const ASN1_PCTX *pctx)
{
    if (X509_NAME_print_ex(out, (const X509_NAME *)*pval,
                           indent, pctx->nm_flags) <= 0)
        return 0;
    return 2;
}