#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_1__* krb5_context ;
struct TYPE_5__ {scalar_t__ num_cc_ops; int /*<<< orphan*/ * cc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _krb5_load_ccache_plugins (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_acc_ops ; 
 int /*<<< orphan*/  krb5_akcm_ops ; 
 int /*<<< orphan*/  krb5_cc_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_fcc_ops ; 
 int /*<<< orphan*/  krb5_kcm_ops ; 
 int /*<<< orphan*/  krb5_mcc_ops ; 
 int /*<<< orphan*/  krb5_scc_ops ; 

__attribute__((used)) static krb5_error_code
cc_ops_register(krb5_context context)
{
    context->cc_ops = NULL;
    context->num_cc_ops = 0;

#ifndef KCM_IS_API_CACHE
    krb5_cc_register(context, &krb5_acc_ops, TRUE);
#endif
    krb5_cc_register(context, &krb5_fcc_ops, TRUE);
    krb5_cc_register(context, &krb5_mcc_ops, TRUE);
#ifdef HAVE_SCC
    krb5_cc_register(context, &krb5_scc_ops, TRUE);
#endif
#ifdef HAVE_KCM
#ifdef KCM_IS_API_CACHE
    krb5_cc_register(context, &krb5_akcm_ops, TRUE);
#endif
    krb5_cc_register(context, &krb5_kcm_ops, TRUE);
#endif
    _krb5_load_ccache_plugins(context);
    return 0;
}