#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_19__ {TYPE_7__* server; } ;
typedef  TYPE_3__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache_data ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_4__* kcm_ccache ;
struct TYPE_17__ {int len; int /*<<< orphan*/ * val; } ;
struct TYPE_18__ {TYPE_1__ name_string; } ;
struct TYPE_21__ {TYPE_2__ name; } ;
struct TYPE_20__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ KRB5_FCC_PERM ; 
 int KRB5_GC_CACHED ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 scalar_t__ disallow_getting_krbtgt ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kcm_ccache_resolve_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_4__**) ; 
 scalar_t__ kcm_ccache_retrieve_cred (int /*<<< orphan*/ ,TYPE_4__*,int,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  kcm_internal_ccache (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ krb5_get_credentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_is_config_principal (int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ krb5_ret_creds_tag (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ krb5_ret_uint32 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ krb5_store_creds (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
kcm_op_retrieve(krb5_context context,
		kcm_client *client,
		kcm_operation opcode,
		krb5_storage *request,
		krb5_storage *response)
{
    uint32_t flags;
    krb5_creds mcreds;
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;
    krb5_creds *credp;
    int free_creds = 0;

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = krb5_ret_uint32(request, &flags);
    if (ret) {
	free(name);
	return ret;
    }

    ret = krb5_ret_creds_tag(request, &mcreds);
    if (ret) {
	free(name);
	return ret;
    }

    if (disallow_getting_krbtgt &&
	mcreds.server->name.name_string.len == 2 &&
	strcmp(mcreds.server->name.name_string.val[0], KRB5_TGS_NAME) == 0)
    {
	free(name);
	krb5_free_cred_contents(context, &mcreds);
	return KRB5_FCC_PERM;
    }

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    if (ret) {
	free(name);
	krb5_free_cred_contents(context, &mcreds);
	return ret;
    }

    ret = kcm_ccache_retrieve_cred(context, ccache, flags,
				   &mcreds, &credp);
    if (ret && ((flags & KRB5_GC_CACHED) == 0) &&
	!krb5_is_config_principal(context, mcreds.server)) {
	krb5_ccache_data ccdata;

	/* try and acquire */
	HEIMDAL_MUTEX_lock(&ccache->mutex);

	/* Fake up an internal ccache */
	kcm_internal_ccache(context, ccache, &ccdata);

	/* glue cc layer will store creds */
	ret = krb5_get_credentials(context, 0, &ccdata, &mcreds, &credp);
	if (ret == 0)
	    free_creds = 1;

	HEIMDAL_MUTEX_unlock(&ccache->mutex);
    }

    if (ret == 0) {
	ret = krb5_store_creds(response, credp);
    }

    free(name);
    krb5_free_cred_contents(context, &mcreds);
    kcm_release_ccache(context, ccache);

    if (free_creds)
	krb5_free_cred_contents(context, credp);

    return ret;
}