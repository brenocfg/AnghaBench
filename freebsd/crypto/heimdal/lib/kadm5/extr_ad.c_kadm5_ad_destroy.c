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
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_3__ {int /*<<< orphan*/  context; scalar_t__ my_context; int /*<<< orphan*/  caller; scalar_t__ client_name; scalar_t__ realm; scalar_t__ base_dn; scalar_t__ ccache; } ;
typedef  TYPE_1__ kadm5_ad_context ;
typedef  int /*<<< orphan*/  LDAP ;

/* Variables and functions */
 int /*<<< orphan*/ * CTX2LP (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_ad_destroy(void *server_handle)
{
    kadm5_ad_context *context = server_handle;

    if (context->ccache)
	krb5_cc_destroy(context->context, context->ccache);

#ifdef OPENLDAP
    {
	LDAP *lp = CTX2LP(context);
	if (lp)
	    ldap_unbind(lp);
	if (context->base_dn)
	    free(context->base_dn);
    }
#endif
    free(context->realm);
    free(context->client_name);
    krb5_free_principal(context->context, context->caller);
    if(context->my_context)
	krb5_free_context(context->context);
    return 0;
}