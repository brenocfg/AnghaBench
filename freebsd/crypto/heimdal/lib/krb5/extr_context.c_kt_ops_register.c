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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_1__* krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/ * kt_types; scalar_t__ num_kt_types; } ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_akf_ops ; 
 int /*<<< orphan*/  krb5_any_ops ; 
 int /*<<< orphan*/  krb5_fkt_ops ; 
 int /*<<< orphan*/  krb5_javakt_ops ; 
 int /*<<< orphan*/  krb5_kt_register (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_mkt_ops ; 
 int /*<<< orphan*/  krb5_wrfkt_ops ; 

__attribute__((used)) static krb5_error_code
kt_ops_register(krb5_context context)
{
    context->num_kt_types = 0;
    context->kt_types     = NULL;

    krb5_kt_register (context, &krb5_fkt_ops);
    krb5_kt_register (context, &krb5_wrfkt_ops);
    krb5_kt_register (context, &krb5_javakt_ops);
    krb5_kt_register (context, &krb5_mkt_ops);
#ifndef HEIMDAL_SMALLER
    krb5_kt_register (context, &krb5_akf_ops);
#endif
    krb5_kt_register (context, &krb5_any_ops);
    return 0;
}