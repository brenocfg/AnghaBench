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
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_3__ {int mask; int /*<<< orphan*/  realm; } ;
typedef  TYPE_1__ kadm5_config_params ;

/* Variables and functions */
 int KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
_kadm5_marshal_params(krb5_context context,
		      kadm5_config_params *params,
		      krb5_data *out)
{
    krb5_storage *sp = krb5_storage_emem();

    krb5_store_int32(sp, params->mask & (KADM5_CONFIG_REALM));

    if(params->mask & KADM5_CONFIG_REALM)
	krb5_store_string(sp, params->realm);
    krb5_storage_to_data(sp, out);
    krb5_storage_free(sp);

    return 0;
}