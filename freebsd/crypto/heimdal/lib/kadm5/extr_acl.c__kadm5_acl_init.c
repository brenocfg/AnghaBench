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
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {int /*<<< orphan*/  acl_flags; int /*<<< orphan*/  context; int /*<<< orphan*/  caller; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  KADM5_ADMIN_SERVICE ; 
 int /*<<< orphan*/  KADM5_PRIV_ALL ; 
 scalar_t__ fetch_acl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kadm5_ret_t
_kadm5_acl_init(kadm5_server_context *context)
{
    krb5_principal princ;
    krb5_error_code ret;

    ret = krb5_parse_name(context->context, KADM5_ADMIN_SERVICE, &princ);
    if (ret)
	return ret;
    ret = krb5_principal_compare(context->context, context->caller, princ);
    krb5_free_principal(context->context, princ);
    if(ret != 0) {
	context->acl_flags = KADM5_PRIV_ALL;
	return 0;
    }

    return fetch_acl (context, NULL, &context->acl_flags);
}