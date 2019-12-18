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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_7__ {TYPE_2__* proxyPolicy; scalar_t__ pcPathLengthConstraint; } ;
struct TYPE_6__ {TYPE_1__* policy; int /*<<< orphan*/  policyLanguage; } ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_3__ PROXY_CERT_INFO_EXTENSION ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2a_ASN1_INTEGER (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2r_pci(X509V3_EXT_METHOD *method, PROXY_CERT_INFO_EXTENSION *pci,
                   BIO *out, int indent)
{
    BIO_printf(out, "%*sPath Length Constraint: ", indent, "");
    if (pci->pcPathLengthConstraint)
        i2a_ASN1_INTEGER(out, pci->pcPathLengthConstraint);
    else
        BIO_printf(out, "infinite");
    BIO_puts(out, "\n");
    BIO_printf(out, "%*sPolicy Language: ", indent, "");
    i2a_ASN1_OBJECT(out, pci->proxyPolicy->policyLanguage);
    BIO_puts(out, "\n");
    if (pci->proxyPolicy->policy && pci->proxyPolicy->policy->data)
        BIO_printf(out, "%*sPolicy Text: %s\n", indent, "",
                   pci->proxyPolicy->policy->data);
    return 1;
}