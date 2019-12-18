#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {scalar_t__ endtime; } ;
struct TYPE_8__ {TYPE_1__ times; int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_const_realm ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  in_cred ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ KRB5_PRINC_NOMATCH ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 int /*<<< orphan*/  _gsskrb5_clear_status () ; 
 scalar_t__ krb5_cc_retrieve_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

OM_uint32
__gsskrb5_ccache_lifetime(OM_uint32 *minor_status,
			  krb5_context context,
			  krb5_ccache id,
			  krb5_principal principal,
			  OM_uint32 *lifetime)
{
    krb5_creds in_cred, out_cred;
    krb5_const_realm realm;
    krb5_error_code kret;

    memset(&in_cred, 0, sizeof(in_cred));
    in_cred.client = principal;

    realm = krb5_principal_get_realm(context,  principal);
    if (realm == NULL) {
	_gsskrb5_clear_status ();
	*minor_status = KRB5_PRINC_NOMATCH; /* XXX */
	return GSS_S_FAILURE;
    }

    kret = krb5_make_principal(context, &in_cred.server,
			       realm, KRB5_TGS_NAME, realm, NULL);
    if (kret) {
	*minor_status = kret;
	return GSS_S_FAILURE;
    }

    kret = krb5_cc_retrieve_cred(context, id, 0, &in_cred, &out_cred);
    krb5_free_principal(context, in_cred.server);
    if (kret) {
	*minor_status = 0;
	*lifetime = 0;
	return GSS_S_COMPLETE;
    }

    *lifetime = out_cred.times.endtime;
    krb5_free_cred_contents(context, &out_cred);

    return GSS_S_COMPLETE;
}