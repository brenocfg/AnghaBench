#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_2__* kcm_ccache ;
typedef  scalar_t__ int8_t ;
struct TYPE_6__ {int /*<<< orphan*/  keyblock; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; TYPE_1__ key; int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_FLAGS_USE_CACHED_KEY ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kcm_ccache_enqueue_default (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kcm_ccache_resolve_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__**) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_keyblock_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_int8 (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ krb5_ret_keyblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static krb5_error_code
kcm_op_get_initial_ticket(krb5_context context,
			  kcm_client *client,
			  kcm_operation opcode,
			  krb5_storage *request,
			  krb5_storage *response)
{
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;
    int8_t not_tgt = 0;
    krb5_principal server = NULL;
    krb5_keyblock key;

    krb5_keyblock_zero(&key);

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = krb5_ret_int8(request, &not_tgt);
    if (ret) {
	free(name);
	return ret;
    }

    if (not_tgt) {
	ret = krb5_ret_principal(request, &server);
	if (ret) {
	    free(name);
	    return ret;
	}
    }

    ret = krb5_ret_keyblock(request, &key);
    if (ret) {
	free(name);
	if (server != NULL)
	    krb5_free_principal(context, server);
	return ret;
    }

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    if (ret == 0) {
	HEIMDAL_MUTEX_lock(&ccache->mutex);

	if (ccache->server != NULL) {
	    krb5_free_principal(context, ccache->server);
	    ccache->server = NULL;
	}

	krb5_free_keyblock(context, &ccache->key.keyblock);

	ccache->server = server;
	ccache->key.keyblock = key;
    	ccache->flags |= KCM_FLAGS_USE_CACHED_KEY;

	ret = kcm_ccache_enqueue_default(context, ccache, NULL);
	if (ret) {
	    ccache->server = NULL;
	    krb5_keyblock_zero(&ccache->key.keyblock);
	    ccache->flags &= ~(KCM_FLAGS_USE_CACHED_KEY);
	}

	HEIMDAL_MUTEX_unlock(&ccache->mutex);
    }

    free(name);

    if (ret != 0) {
	krb5_free_principal(context, server);
	krb5_free_keyblock(context, &key);
    }

    kcm_release_ccache(context, ccache);

    return ret;
}