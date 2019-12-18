#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/ * krb5_principal ;
struct TYPE_16__ {int /*<<< orphan*/  i; } ;
typedef  TYPE_3__ krb5_kdc_flags ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_15__ {scalar_t__ endtime; } ;
struct TYPE_14__ {int /*<<< orphan*/  keytype; } ;
struct TYPE_17__ {TYPE_2__ times; int /*<<< orphan*/ * server; int /*<<< orphan*/  client; TYPE_1__ session; } ;
typedef  TYPE_4__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache_data ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_5__* kcm_ccache ;
typedef  int /*<<< orphan*/  in ;
struct TYPE_18__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kcm_ccache_resolve_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_5__**) ; 
 int /*<<< orphan*/  kcm_internal_ccache (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_credentials_with_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__**) ; 
 scalar_t__ krb5_ret_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ krb5_ret_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
kcm_op_get_ticket(krb5_context context,
		  kcm_client *client,
		  kcm_operation opcode,
		  krb5_storage *request,
		  krb5_storage *response)
{
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;
    krb5_principal server = NULL;
    krb5_ccache_data ccdata;
    krb5_creds in, *out;
    krb5_kdc_flags flags;

    memset(&in, 0, sizeof(in));

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = krb5_ret_uint32(request, &flags.i);
    if (ret) {
	free(name);
	return ret;
    }

    ret = krb5_ret_int32(request, &in.session.keytype);
    if (ret) {
	free(name);
	return ret;
    }

    ret = krb5_ret_principal(request, &server);
    if (ret) {
	free(name);
	return ret;
    }

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    if (ret) {
	krb5_free_principal(context, server);
	free(name);
	return ret;
    }

    HEIMDAL_MUTEX_lock(&ccache->mutex);

    /* Fake up an internal ccache */
    kcm_internal_ccache(context, ccache, &ccdata);

    in.client = ccache->client;
    in.server = server;
    in.times.endtime = 0;

    /* glue cc layer will store creds */
    ret = krb5_get_credentials_with_flags(context, 0, flags,
					  &ccdata, &in, &out);

    HEIMDAL_MUTEX_unlock(&ccache->mutex);

    krb5_free_principal(context, server);

    if (ret == 0)
	krb5_free_cred_contents(context, out);

    kcm_release_ccache(context, ccache);
    free(name);

    return ret;
}