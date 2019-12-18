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
typedef  int /*<<< orphan*/  krb5_prompter_fct ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_config_params ;
struct TYPE_3__ {char const* keytab; int sock; int /*<<< orphan*/  ccache; int /*<<< orphan*/  prompter; int /*<<< orphan*/ * service_name; int /*<<< orphan*/ * client_name; } ;
typedef  TYPE_1__ kadm5_client_context ;

/* Variables and functions */
 scalar_t__ _kadm5_c_get_cred_cache (int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _kadm5_c_init_context (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_c_init_with_context(krb5_context context,
			  const char *client_name,
			  const char *password,
			  krb5_prompter_fct prompter,
			  const char *keytab,
			  krb5_ccache ccache,
			  const char *service_name,
			  kadm5_config_params *realm_params,
			  unsigned long struct_version,
			  unsigned long api_version,
			  void **server_handle)
{
    kadm5_ret_t ret;
    kadm5_client_context *ctx;
    krb5_ccache cc;

    ret = _kadm5_c_init_context(&ctx, realm_params, context);
    if(ret)
	return ret;

    if(password != NULL && *password != '\0') {
	ret = _kadm5_c_get_cred_cache(context,
				      client_name,
				      service_name,
				      password, prompter, keytab, ccache, &cc);
	if(ret)
	    return ret; /* XXX */
	ccache = cc;
    }


    if (client_name != NULL)
	ctx->client_name = strdup(client_name);
    else
	ctx->client_name = NULL;
    if (service_name != NULL)
	ctx->service_name = strdup(service_name);
    else
	ctx->service_name = NULL;
    ctx->prompter = prompter;
    ctx->keytab = keytab;
    ctx->ccache = ccache;
    /* maybe we should copy the params here */
    ctx->sock = -1;

    *server_handle = ctx;
    return 0;
}