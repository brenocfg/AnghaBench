#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_11__ {int /*<<< orphan*/  endtime; } ;
struct TYPE_12__ {int /*<<< orphan*/ * client; TYPE_1__ times; } ;
typedef  TYPE_2__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
typedef  TYPE_3__* gsskrb5_cred ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  gss_cred_usage_t ;
typedef  scalar_t__ gss_const_OID ;
typedef  TYPE_4__* gss_buffer_t ;
typedef  int /*<<< orphan*/  cred ;
struct TYPE_14__ {int /*<<< orphan*/  value; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ccache; int /*<<< orphan*/  lifetime; int /*<<< orphan*/ * principal; int /*<<< orphan*/  cred_flags; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GSS_CF_DESTROY_CRED_ON_RELEASE ; 
 int /*<<< orphan*/  GSS_C_CRED_PASSWORD ; 
 scalar_t__ GSS_C_NO_OID ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ KRB5_NOCREDS_SUPPLIED ; 
 scalar_t__ __gsskrb5_ccache_lifetime (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_keytab (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ gss_oid_equal (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_cache_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_default_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_get_init_creds_keytab (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_password (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OM_uint32 acquire_initiator_cred
		  (OM_uint32 * minor_status,
		   krb5_context context,
		   gss_const_OID credential_type,
		   const void *credential_data,
		   const gss_name_t desired_name,
		   OM_uint32 time_req,
		   gss_const_OID desired_mech,
		   gss_cred_usage_t cred_usage,
		   gsskrb5_cred handle
		  )
{
    OM_uint32 ret;
    krb5_creds cred;
    krb5_principal def_princ;
    krb5_get_init_creds_opt *opt;
    krb5_ccache ccache;
    krb5_keytab keytab;
    krb5_error_code kret;

    keytab = NULL;
    ccache = NULL;
    def_princ = NULL;
    ret = GSS_S_FAILURE;
    memset(&cred, 0, sizeof(cred));

    /*
     * If we have a preferred principal, lets try to find it in all
     * caches, otherwise, fall back to default cache, ignore all
     * errors while searching.
     */

    if (credential_type != GSS_C_NO_OID &&
	!gss_oid_equal(credential_type, GSS_C_CRED_PASSWORD)) {
	kret = KRB5_NOCREDS_SUPPLIED; /* XXX */
	goto end;
    }

    if (handle->principal) {
	kret = krb5_cc_cache_match (context,
				    handle->principal,
				    &ccache);
	if (kret == 0) {
	    ret = GSS_S_COMPLETE;
	    goto found;
	}
    }

    if (ccache == NULL) {
	kret = krb5_cc_default(context, &ccache);
	if (kret)
	    goto end;
    }
    kret = krb5_cc_get_principal(context, ccache, &def_princ);
    if (kret != 0) {
	/* we'll try to use a keytab below */
	krb5_cc_close(context, ccache);
	def_princ = NULL;
	kret = 0;
    } else if (handle->principal == NULL)  {
	kret = krb5_copy_principal(context, def_princ, &handle->principal);
	if (kret)
	    goto end;
    } else if (handle->principal != NULL &&
	       krb5_principal_compare(context, handle->principal,
				      def_princ) == FALSE) {
	krb5_free_principal(context, def_princ);
	def_princ = NULL;
	krb5_cc_close(context, ccache);
	ccache = NULL;
    }
    if (def_princ == NULL) {
	/* We have no existing credentials cache,
	 * so attempt to get a TGT using a keytab.
	 */
	if (handle->principal == NULL) {
	    kret = krb5_get_default_principal(context, &handle->principal);
	    if (kret)
		goto end;
	}
	kret = krb5_get_init_creds_opt_alloc(context, &opt);
	if (kret)
	    goto end;
	if (credential_type != GSS_C_NO_OID &&
	    gss_oid_equal(credential_type, GSS_C_CRED_PASSWORD)) {
	    gss_buffer_t password = (gss_buffer_t)credential_data;

	    /* XXX are we requiring password to be NUL terminated? */

	    kret = krb5_get_init_creds_password(context, &cred,
						handle->principal,
						password->value,
						NULL, NULL, 0, NULL, opt);
	} else {
	    kret = get_keytab(context, &keytab);
	    if (kret) {
		krb5_get_init_creds_opt_free(context, opt);
		goto end;
	    }
	    kret = krb5_get_init_creds_keytab(context, &cred,
					      handle->principal, keytab,
					      0, NULL, opt);
	}
	krb5_get_init_creds_opt_free(context, opt);
	if (kret)
	    goto end;
	kret = krb5_cc_new_unique(context, krb5_cc_type_memory,
				  NULL, &ccache);
	if (kret)
	    goto end;
	kret = krb5_cc_initialize(context, ccache, cred.client);
	if (kret) {
	    krb5_cc_destroy(context, ccache);
	    goto end;
	}
	kret = krb5_cc_store_cred(context, ccache, &cred);
	if (kret) {
	    krb5_cc_destroy(context, ccache);
	    goto end;
	}
	handle->lifetime = cred.times.endtime;
	handle->cred_flags |= GSS_CF_DESTROY_CRED_ON_RELEASE;
    } else {

	ret = __gsskrb5_ccache_lifetime(minor_status,
					context,
					ccache,
					handle->principal,
					&handle->lifetime);
	if (ret != GSS_S_COMPLETE) {
	    krb5_cc_close(context, ccache);
	    goto end;
	}
	kret = 0;
    }
 found:
    handle->ccache = ccache;
    ret = GSS_S_COMPLETE;

end:
    if (cred.client != NULL)
	krb5_free_cred_contents(context, &cred);
    if (def_princ != NULL)
	krb5_free_principal(context, def_princ);
    if (keytab != NULL)
	krb5_kt_close(context, keytab);
    if (ret != GSS_S_COMPLETE && kret != 0)
	*minor_status = kret;
    return (ret);
}