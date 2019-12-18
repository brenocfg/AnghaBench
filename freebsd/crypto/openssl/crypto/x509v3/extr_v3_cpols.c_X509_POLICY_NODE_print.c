#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ X509_POLICY_NODE ;
struct TYPE_6__ {scalar_t__ qualifier_set; int /*<<< orphan*/  valid_policy; } ;
typedef  TYPE_2__ X509_POLICY_DATA ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ node_data_critical (TYPE_2__ const*) ; 
 int /*<<< orphan*/  print_qualifiers (int /*<<< orphan*/ *,scalar_t__,int) ; 

void X509_POLICY_NODE_print(BIO *out, X509_POLICY_NODE *node, int indent)
{
    const X509_POLICY_DATA *dat = node->data;

    BIO_printf(out, "%*sPolicy: ", indent, "");

    i2a_ASN1_OBJECT(out, dat->valid_policy);
    BIO_puts(out, "\n");
    BIO_printf(out, "%*s%s\n", indent + 2, "",
               node_data_critical(dat) ? "Critical" : "Non Critical");
    if (dat->qualifier_set)
        print_qualifiers(out, dat->qualifier_set, indent + 2);
    else
        BIO_printf(out, "%*sNo Qualifiers\n", indent + 2, "");
}