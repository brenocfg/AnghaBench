#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_cred ;
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_GC_CACHED ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_credentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__**) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

krb5_error_code
_krb5_get_krbtgt(krb5_context context,
		 krb5_ccache  id,
		 krb5_realm realm,
		 krb5_creds **cred)
{
    krb5_error_code ret;
    krb5_creds tmp_cred;

    memset(&tmp_cred, 0, sizeof(tmp_cred));

    ret = krb5_cc_get_principal(context, id, &tmp_cred.client);
    if (ret)
	return ret;

    ret = krb5_make_principal(context,
			      &tmp_cred.server,
			      realm,
			      KRB5_TGS_NAME,
			      realm,
			      NULL);
    if(ret) {
	krb5_free_principal(context, tmp_cred.client);
	return ret;
    }
    ret = krb5_get_credentials(context,
			       KRB5_GC_CACHED,
			       id,
			       &tmp_cred,
			       cred);
    krb5_free_principal(context, tmp_cred.client);
    krb5_free_principal(context, tmp_cred.server);
    if(ret)
	return ret;
    return 0;
}