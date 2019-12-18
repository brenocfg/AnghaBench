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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_3__ {int /*<<< orphan*/  ccache; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_ad_context ;

/* Variables and functions */
 scalar_t__ ad_get_cred (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_set_password_using_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_ad_chpass_principal(void *server_handle,
			  krb5_principal principal,
			  const char *password)
{
    kadm5_ad_context *context = server_handle;
    krb5_data result_code_string, result_string;
    int result_code;
    kadm5_ret_t ret;

    ret = ad_get_cred(context, NULL);
    if (ret)
	return ret;

    krb5_data_zero (&result_code_string);
    krb5_data_zero (&result_string);

    ret = krb5_set_password_using_ccache (context->context,
					  context->ccache,
					  password,
					  principal,
					  &result_code,
					  &result_code_string,
					  &result_string);

    krb5_data_free (&result_code_string);
    krb5_data_free (&result_string);

    /* XXX do mapping here on error codes */

    return ret;
}