#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
struct TYPE_2__ {int my_context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_config_params ;

/* Variables and functions */
 scalar_t__ kadm5_s_init_with_creds_ctx (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,unsigned long,unsigned long,void**) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 

kadm5_ret_t
kadm5_s_init_with_creds(const char *client_name,
			krb5_ccache ccache,
			const char *service_name,
			kadm5_config_params *realm_params,
			unsigned long struct_version,
			unsigned long api_version,
			void **server_handle)
{
    krb5_context context;
    kadm5_ret_t ret;
    kadm5_server_context *ctx;

    ret = krb5_init_context(&context);
    if (ret)
	return ret;
    ret = kadm5_s_init_with_creds_ctx(context,
				      client_name,
				      ccache,
				      service_name,
				      realm_params,
				      struct_version,
				      api_version,
				      server_handle);
    if(ret){
	krb5_free_context(context);
	return ret;
    }
    ctx = *server_handle;
    ctx->my_context = 1;
    return 0;
}