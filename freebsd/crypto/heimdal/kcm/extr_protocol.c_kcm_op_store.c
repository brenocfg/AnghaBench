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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  int /*<<< orphan*/  kcm_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_LOG_REQUEST_NAME (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kcm_ccache_enqueue_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kcm_ccache_resolve_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ kcm_ccache_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_ret_stringz (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static krb5_error_code
kcm_op_store(krb5_context context,
	     kcm_client *client,
	     kcm_operation opcode,
	     krb5_storage *request,
	     krb5_storage *response)
{
    krb5_creds creds;
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = krb5_ret_creds(request, &creds);
    if (ret) {
	free(name);
	return ret;
    }

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    if (ret) {
	free(name);
	krb5_free_cred_contents(context, &creds);
	return ret;
    }

    ret = kcm_ccache_store_cred(context, ccache, &creds, 0);
    if (ret) {
	free(name);
	krb5_free_cred_contents(context, &creds);
	kcm_release_ccache(context, ccache);
	return ret;
    }

    kcm_ccache_enqueue_default(context, ccache, &creds);

    free(name);
    kcm_release_ccache(context, ccache);

    return 0;
}