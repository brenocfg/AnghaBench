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
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_ad_context ;

/* Variables and functions */
 scalar_t__ KADM5_RPC_ERROR ; 
 scalar_t__ _kadm5_ad_connect (void*) ; 
 scalar_t__ ad_get_cred (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_ad_get_principals(void *server_handle,
			const char *expression,
			char ***principals,
			int *count)
{
    kadm5_ad_context *context = server_handle;

    /*
     * KADM5_PRINCIPAL | KADM5_KVNO | KADM5_ATTRIBUTES
     */

#ifdef OPENLDAP
    kadm5_ret_t ret;

    ret = ad_get_cred(context, NULL);
    if (ret)
	return ret;

    ret = _kadm5_ad_connect(server_handle);
    if (ret)
	return ret;

    krb5_set_error_message(context->context, KADM5_RPC_ERROR, "Function not implemented");
    return KADM5_RPC_ERROR;
#else
    krb5_set_error_message(context->context, KADM5_RPC_ERROR, "Function not implemented");
    return KADM5_RPC_ERROR;
#endif
}