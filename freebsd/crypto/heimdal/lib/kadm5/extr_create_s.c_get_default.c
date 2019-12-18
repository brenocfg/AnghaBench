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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_const_realm ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_PRINCIPAL_NORMAL_MASK ; 
 scalar_t__ kadm5_s_get_principal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kadm5_ret_t
get_default(kadm5_server_context *context, krb5_principal princ,
	    kadm5_principal_ent_t def)
{
    kadm5_ret_t ret;
    krb5_principal def_principal;
    krb5_const_realm realm = krb5_principal_get_realm(context->context, princ);

    ret = krb5_make_principal(context->context, &def_principal,
			      realm, "default", NULL);
    if (ret)
	return ret;
    ret = kadm5_s_get_principal(context, def_principal, def,
				KADM5_PRINCIPAL_NORMAL_MASK);
    krb5_free_principal (context->context, def_principal);
    return ret;
}