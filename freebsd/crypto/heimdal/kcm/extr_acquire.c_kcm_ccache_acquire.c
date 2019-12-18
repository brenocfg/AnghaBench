#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_realm ;
typedef  int /*<<< orphan*/  krb5_ccache_data ;
typedef  TYPE_3__* kcm_ccache ;
typedef  int /*<<< orphan*/  cred ;
struct TYPE_10__ {scalar_t__ length; } ;
struct TYPE_13__ {TYPE_1__ keyvalue; } ;
struct TYPE_11__ {int /*<<< orphan*/ * keytab; TYPE_4__ keyblock; } ;
struct TYPE_12__ {int flags; scalar_t__ tkt_life; scalar_t__ renew_life; int /*<<< orphan*/  mutex; int /*<<< orphan*/  name; TYPE_2__ key; int /*<<< orphan*/  client; int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_3__*) ; 
 int KCM_FLAGS_USE_CACHED_KEY ; 
 int KCM_FLAGS_USE_KEYTAB ; 
 scalar_t__ KRB5_FCC_INTERNAL ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kcm_ccache_remove_creds_internal (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ kcm_ccache_store_cred_internal (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kcm_internal_ccache (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_err_text (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_get_init_creds_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_keytab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_default_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_renew_life (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_tkt_life (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

krb5_error_code
kcm_ccache_acquire(krb5_context context,
		   kcm_ccache ccache,
		   krb5_creds **credp)
{
    krb5_error_code ret = 0;
    krb5_creds cred;
    krb5_const_realm realm;
    krb5_get_init_creds_opt *opt = NULL;
    krb5_ccache_data ccdata;
    char *in_tkt_service = NULL;

    memset(&cred, 0, sizeof(cred));

    KCM_ASSERT_VALID(ccache);

    /* We need a cached key or keytab to acquire credentials */
    if (ccache->flags & KCM_FLAGS_USE_CACHED_KEY) {
	if (ccache->key.keyblock.keyvalue.length == 0)
	    krb5_abortx(context,
			"kcm_ccache_acquire: KCM_FLAGS_USE_CACHED_KEY without key");
    } else if (ccache->flags & KCM_FLAGS_USE_KEYTAB) {
	if (ccache->key.keytab == NULL)
	    krb5_abortx(context,
			"kcm_ccache_acquire: KCM_FLAGS_USE_KEYTAB without keytab");
    } else {
	kcm_log(0, "Cannot acquire initial credentials for cache %s without key",
		ccache->name);
	return KRB5_FCC_INTERNAL;
    }

    HEIMDAL_MUTEX_lock(&ccache->mutex);

    /* Fake up an internal ccache */
    kcm_internal_ccache(context, ccache, &ccdata);

    /* Now, actually acquire the creds */
    if (ccache->server != NULL) {
	ret = krb5_unparse_name(context, ccache->server, &in_tkt_service);
	if (ret) {
	    kcm_log(0, "Failed to unparse service principal name for cache %s: %s",
		    ccache->name, krb5_get_err_text(context, ret));
	    return ret;
	}
    }

    realm = krb5_principal_get_realm(context, ccache->client);

    ret = krb5_get_init_creds_opt_alloc(context, &opt);
    if (ret)
	goto out;
    krb5_get_init_creds_opt_set_default_flags(context, "kcm", realm, opt);
    if (ccache->tkt_life != 0)
	krb5_get_init_creds_opt_set_tkt_life(opt, ccache->tkt_life);
    if (ccache->renew_life != 0)
	krb5_get_init_creds_opt_set_renew_life(opt, ccache->renew_life);

    if (ccache->flags & KCM_FLAGS_USE_CACHED_KEY) {
	ret = krb5_get_init_creds_keyblock(context,
					   &cred,
					   ccache->client,
					   &ccache->key.keyblock,
					   0,
					   in_tkt_service,
					   opt);
    } else {
	/* loosely based on lib/krb5/init_creds_pw.c */
	ret = krb5_get_init_creds_keytab(context,
					 &cred,
					 ccache->client,
					 ccache->key.keytab,
					 0,
					 in_tkt_service,
					 opt);
    }

    if (ret) {
	kcm_log(0, "Failed to acquire credentials for cache %s: %s",
		ccache->name, krb5_get_err_text(context, ret));
	if (in_tkt_service != NULL)
	    free(in_tkt_service);
	goto out;
    }

    if (in_tkt_service != NULL)
	free(in_tkt_service);

    /* Swap them in */
    kcm_ccache_remove_creds_internal(context, ccache);

    ret = kcm_ccache_store_cred_internal(context, ccache, &cred, 0, credp);
    if (ret) {
	kcm_log(0, "Failed to store credentials for cache %s: %s",
		ccache->name, krb5_get_err_text(context, ret));
	krb5_free_cred_contents(context, &cred);
	goto out;
    }

out:
    if (opt)
	krb5_get_init_creds_opt_free(context, opt);

    HEIMDAL_MUTEX_unlock(&ccache->mutex);

    return ret;
}