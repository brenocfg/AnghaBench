#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_11__ {int mask; char const* realm; } ;
typedef  TYPE_1__ kadm5_config_params ;
struct TYPE_12__ {void* client_name; int /*<<< orphan*/ * realm; int /*<<< orphan*/  context; int /*<<< orphan*/  caller; } ;
typedef  TYPE_2__ kadm5_ad_context ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int KADM5_CONFIG_REALM ; 
 scalar_t__ _kadm5_ad_connect (TYPE_2__*) ; 
 scalar_t__ ad_get_cred (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  initialize_kadm5_error_table_r ; 
 int /*<<< orphan*/  kadm5_ad_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_add_et_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_default_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_funcs (TYPE_2__*) ; 
 void* strdup (char const*) ; 

kadm5_ret_t
kadm5_ad_init_with_password_ctx(krb5_context context,
				const char *client_name,
				const char *password,
				const char *service_name,
				kadm5_config_params *realm_params,
				unsigned long struct_version,
				unsigned long api_version,
				void **server_handle)
{
    kadm5_ret_t ret;
    kadm5_ad_context *ctx;

    ctx = malloc(sizeof(*ctx));
    if(ctx == NULL)
	return ENOMEM;
    memset(ctx, 0, sizeof(*ctx));
    set_funcs(ctx);

    ctx->context = context;
    krb5_add_et_list (context, initialize_kadm5_error_table_r);

    ret = krb5_parse_name(ctx->context, client_name, &ctx->caller);
    if(ret) {
	free(ctx);
	return ret;
    }

    if(realm_params->mask & KADM5_CONFIG_REALM) {
	ret = 0;
	ctx->realm = strdup(realm_params->realm);
	if (ctx->realm == NULL)
	    ret = ENOMEM;
    } else
	ret = krb5_get_default_realm(ctx->context, &ctx->realm);
    if (ret) {
	free(ctx);
	return ret;
    }

    ctx->client_name = strdup(client_name);

    if(password != NULL && *password != '\0')
	ret = ad_get_cred(ctx, password);
    else
	ret = ad_get_cred(ctx, NULL);
    if(ret) {
	kadm5_ad_destroy(ctx);
	return ret;
    }

#ifdef OPENLDAP
    ret = _kadm5_ad_connect(ctx);
    if (ret) {
	kadm5_ad_destroy(ctx);
	return ret;
    }
#endif

    *server_handle = ctx;
    return 0;
}