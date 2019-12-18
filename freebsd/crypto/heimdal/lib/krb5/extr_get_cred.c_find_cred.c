#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_11__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_CC_NOTFOUND ; 
 int /*<<< orphan*/  KRB5_TC_DONT_MATCH_REALM ; 
 int /*<<< orphan*/  krb5_cc_clear_mcred (TYPE_1__*) ; 
 scalar_t__ krb5_cc_retrieve_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ krb5_compare_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ krb5_copy_creds_contents (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ not_found (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
find_cred(krb5_context context,
	  krb5_ccache id,
	  krb5_principal server,
	  krb5_creds **tgts,
	  krb5_creds *out_creds)
{
    krb5_error_code ret;
    krb5_creds mcreds;

    krb5_cc_clear_mcred(&mcreds);
    mcreds.server = server;
    ret = krb5_cc_retrieve_cred(context, id, KRB5_TC_DONT_MATCH_REALM,
				&mcreds, out_creds);
    if(ret == 0)
	return 0;
    while(tgts && *tgts){
	if(krb5_compare_creds(context, KRB5_TC_DONT_MATCH_REALM,
			      &mcreds, *tgts)){
	    ret = krb5_copy_creds_contents(context, *tgts, out_creds);
	    return ret;
	}
	tgts++;
    }
    return not_found(context, server, KRB5_CC_NOTFOUND);
}