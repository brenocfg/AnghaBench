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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_3__ {int mask; int /*<<< orphan*/  realm; } ;
typedef  TYPE_1__ kadm5_config_params ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int KADM5_CONFIG_REALM ; 
 scalar_t__ krb5_ret_int32 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ krb5_ret_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_data (int /*<<< orphan*/ *) ; 

kadm5_ret_t
_kadm5_unmarshal_params(krb5_context context,
			krb5_data *in,
			kadm5_config_params *params)
{
    krb5_error_code ret;
    krb5_storage *sp;
    int32_t mask;

    sp = krb5_storage_from_data(in);
    if (sp == NULL)
	return ENOMEM;

    ret = krb5_ret_int32(sp, &mask);
    if (ret)
	goto out;
    params->mask = mask;

    if(params->mask & KADM5_CONFIG_REALM)
	ret = krb5_ret_string(sp, &params->realm);
 out:
    krb5_storage_free(sp);

    return ret;
}