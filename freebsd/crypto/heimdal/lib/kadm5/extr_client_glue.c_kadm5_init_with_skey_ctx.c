#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_config_params ;

/* Variables and functions */
 int /*<<< orphan*/  kadm5_c_init_with_skey_ctx (int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,unsigned long,unsigned long,void**) ; 

kadm5_ret_t
kadm5_init_with_skey_ctx(krb5_context context,
			 const char *client_name,
			 const char *keytab,
			 const char *service_name,
			 kadm5_config_params *realm_params,
			 unsigned long struct_version,
			 unsigned long api_version,
			 void **server_handle)
{
    return kadm5_c_init_with_skey_ctx(context,
				      client_name,
				      keytab,
				      service_name,
				      realm_params,
				      struct_version,
				      api_version,
				      server_handle);
}