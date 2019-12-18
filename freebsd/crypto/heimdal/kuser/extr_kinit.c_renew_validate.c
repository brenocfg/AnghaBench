#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int renewable; int renew; int validate; int forwardable; int proxiable; scalar_t__ request_anonymous; } ;
struct TYPE_20__ {TYPE_3__ b; scalar_t__ i; } ;
typedef  TYPE_5__ krb5_kdc_flags ;
typedef  int krb5_error_code ;
typedef  scalar_t__ krb5_deltat ;
struct TYPE_19__ {scalar_t__ endtime; } ;
struct TYPE_16__ {int forwardable; int proxiable; } ;
struct TYPE_17__ {TYPE_1__ b; } ;
struct TYPE_21__ {int /*<<< orphan*/  client; TYPE_4__ times; TYPE_2__ flags; int /*<<< orphan*/  server; } ;
typedef  TYPE_6__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_GC_CACHED ; 
 scalar_t__ anonymous_flag ; 
 scalar_t__ do_afslog ; 
 int forwardable_flag ; 
 int get_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ k_hasafs () ; 
 int /*<<< orphan*/  krb5_afslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_free_creds (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  krb5_get_credentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__**) ; 
 int krb5_get_kdc_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int proxiable_flag ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
renew_validate(krb5_context context,
	       int renew,
	       int validate,
	       krb5_ccache cache,
	       const char *server,
	       krb5_deltat life)
{
    krb5_error_code ret;
    krb5_creds in, *out = NULL;
    krb5_kdc_flags flags;

    memset(&in, 0, sizeof(in));

    ret = krb5_cc_get_principal(context, cache, &in.client);
    if(ret) {
	krb5_warn(context, ret, "krb5_cc_get_principal");
	return ret;
    }
    ret = get_server(context, in.client, server, &in.server);
    if(ret) {
	krb5_warn(context, ret, "get_server");
	goto out;
    }

    if (renew) {
	/*
	 * no need to check the error here, it's only to be
	 * friendly to the user
	 */
	krb5_get_credentials(context, KRB5_GC_CACHED, cache, &in, &out);
    }

    flags.i = 0;
    flags.b.renewable         = flags.b.renew = renew;
    flags.b.validate          = validate;

    if (forwardable_flag != -1)
	flags.b.forwardable       = forwardable_flag;
    else if (out)
	flags.b.forwardable 	  = out->flags.b.forwardable;

    if (proxiable_flag != -1)
	flags.b.proxiable         = proxiable_flag;
    else if (out)
	flags.b.proxiable 	  = out->flags.b.proxiable;

    if (anonymous_flag)
	flags.b.request_anonymous = anonymous_flag;
    if(life)
	in.times.endtime = time(NULL) + life;

    if (out) {
	krb5_free_creds (context, out);
	out = NULL;
    }


    ret = krb5_get_kdc_cred(context,
			    cache,
			    flags,
			    NULL,
			    NULL,
			    &in,
			    &out);
    if(ret) {
	krb5_warn(context, ret, "krb5_get_kdc_cred");
	goto out;
    }
    ret = krb5_cc_initialize(context, cache, in.client);
    if(ret) {
	krb5_free_creds (context, out);
	krb5_warn(context, ret, "krb5_cc_initialize");
	goto out;
    }
    ret = krb5_cc_store_cred(context, cache, out);

    if(ret == 0 && server == NULL) {
	/* only do this if it's a general renew-my-tgt request */
#ifndef NO_AFS
	if(do_afslog && k_hasafs())
	    krb5_afslog(context, cache, NULL, NULL);
#endif
    }

    krb5_free_creds (context, out);
    if(ret) {
	krb5_warn(context, ret, "krb5_cc_store_cred");
	goto out;
    }
out:
    krb5_free_cred_contents(context, &in);
    return ret;
}