#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid ;
struct kcm_creds {int /*<<< orphan*/  cred; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcmuuid_t ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ KRB5_CC_END ; 
 scalar_t__ KRB5_CC_IO ; 
 int /*<<< orphan*/  free (char*) ; 
 struct kcm_creds* kcm_ccache_find_cred_uuid (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kcm_ccache_resolve_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 
 int krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ krb5_store_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
kcm_op_get_cred_by_uuid(krb5_context context,
			kcm_client *client,
			kcm_operation opcode,
			krb5_storage *request,
			krb5_storage *response)
{
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;
    struct kcm_creds *c;
    kcmuuid_t uuid;
    ssize_t sret;

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    free(name);
    if (ret)
	return ret;

    sret = krb5_storage_read(request, &uuid, sizeof(uuid));
    if (sret != sizeof(uuid)) {
	kcm_release_ccache(context, ccache);
	krb5_clear_error_message(context);
	return KRB5_CC_IO;
    }

    c = kcm_ccache_find_cred_uuid(context, ccache, uuid);
    if (c == NULL) {
	kcm_release_ccache(context, ccache);
	return KRB5_CC_END;
    }

    HEIMDAL_MUTEX_lock(&ccache->mutex);
    ret = krb5_store_creds(response, &c->cred);
    HEIMDAL_MUTEX_unlock(&ccache->mutex);

    kcm_release_ccache(context, ccache);

    return ret;
}