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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_11__ {int mask; char* realm; char* admin_server; scalar_t__ kadmind_port; } ;
typedef  TYPE_1__ kadm5_config_params ;
struct TYPE_12__ {scalar_t__ kadmind_port; int /*<<< orphan*/ * admin_server; struct TYPE_12__* realm; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ kadm5_client_context ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int KADM5_CONFIG_ADMIN_SERVER ; 
 int KADM5_CONFIG_KADMIND_PORT ; 
 int KADM5_CONFIG_REALM ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_kadm5_error_table_r ; 
 int /*<<< orphan*/  krb5_add_et_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_krbhst (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_get_default_realm (int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ krb5_get_krb_admin_hst (int /*<<< orphan*/ ,TYPE_2__**,char***) ; 
 scalar_t__ krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_funcs (TYPE_2__*) ; 
 char* strchr (int /*<<< orphan*/ *,char) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int /*<<< orphan*/ ) ; 

kadm5_ret_t
_kadm5_c_init_context(kadm5_client_context **ctx,
		      kadm5_config_params *params,
		      krb5_context context)
{
    krb5_error_code ret;
    char *colon;

    *ctx = malloc(sizeof(**ctx));
    if(*ctx == NULL)
	return ENOMEM;
    memset(*ctx, 0, sizeof(**ctx));
    krb5_add_et_list (context, initialize_kadm5_error_table_r);
    set_funcs(*ctx);
    (*ctx)->context = context;
    if(params->mask & KADM5_CONFIG_REALM) {
	ret = 0;
	(*ctx)->realm = strdup(params->realm);
	if ((*ctx)->realm == NULL)
	    ret = ENOMEM;
    } else
	ret = krb5_get_default_realm((*ctx)->context, &(*ctx)->realm);
    if (ret) {
	free(*ctx);
	return ret;
    }
    if(params->mask & KADM5_CONFIG_ADMIN_SERVER)
	(*ctx)->admin_server = strdup(params->admin_server);
    else {
	char **hostlist;

	ret = krb5_get_krb_admin_hst (context, &(*ctx)->realm, &hostlist);
	if (ret) {
	    free((*ctx)->realm);
	    free(*ctx);
	    return ret;
	}
	(*ctx)->admin_server = strdup(*hostlist);
	krb5_free_krbhst (context, hostlist);
    }

    if ((*ctx)->admin_server == NULL) {
	free((*ctx)->realm);
	free(*ctx);
	return ENOMEM;
    }
    colon = strchr ((*ctx)->admin_server, ':');
    if (colon != NULL)
	*colon++ = '\0';

    (*ctx)->kadmind_port = 0;

    if(params->mask & KADM5_CONFIG_KADMIND_PORT)
	(*ctx)->kadmind_port = params->kadmind_port;
    else if (colon != NULL) {
	char *end;

	(*ctx)->kadmind_port = htons(strtol (colon, &end, 0));
    }
    if ((*ctx)->kadmind_port == 0)
	(*ctx)->kadmind_port = krb5_getportbyname (context, "kerberos-adm",
						   "tcp", 749);
    return 0;
}