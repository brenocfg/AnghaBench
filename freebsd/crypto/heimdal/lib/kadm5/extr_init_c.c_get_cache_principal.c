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
typedef  void* krb5_principal ;
struct TYPE_12__ {scalar_t__ i; } ;
typedef  TYPE_3__ krb5_kdc_flags ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_10__ {scalar_t__ initial; } ;
struct TYPE_11__ {TYPE_1__ b; } ;
struct TYPE_13__ {TYPE_2__ flags; void* server; void* client; } ;
typedef  TYPE_4__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_GC_CACHED ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  krb5_free_creds (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ krb5_get_credentials_with_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__**) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *) ; 
 char* krb5_principal_get_comp_string (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static krb5_error_code
get_cache_principal(krb5_context context,
		    krb5_ccache *id,
		    krb5_principal *client)
{
    krb5_error_code ret;
    const char *name, *inst;
    krb5_principal p1, p2;

    ret = krb5_cc_default(context, id);
    if(ret) {
	*id = NULL;
	return ret;
    }

    ret = krb5_cc_get_principal(context, *id, &p1);
    if(ret) {
	krb5_cc_close(context, *id);
	*id = NULL;
	return ret;
    }

    ret = krb5_make_principal(context, &p2, NULL,
			      "kadmin", "admin", NULL);
    if (ret) {
	krb5_cc_close(context, *id);
	*id = NULL;
	krb5_free_principal(context, p1);
	return ret;
    }

    {
	krb5_creds in, *out;
	krb5_kdc_flags flags;

	flags.i = 0;
	memset(&in, 0, sizeof(in));

	in.client = p1;
	in.server = p2;

	/* check for initial ticket kadmin/admin */
	ret = krb5_get_credentials_with_flags(context, KRB5_GC_CACHED, flags,
					      *id, &in, &out);
	krb5_free_principal(context, p2);
	if (ret == 0) {
	    if (out->flags.b.initial) {
		*client = p1;
		krb5_free_creds(context, out);
		return 0;
	    }
	    krb5_free_creds(context, out);
	}
    }
    krb5_cc_close(context, *id);
    *id = NULL;

    name = krb5_principal_get_comp_string(context, p1, 0);
    inst = krb5_principal_get_comp_string(context, p1, 1);
    if(inst == NULL || strcmp(inst, "admin") != 0) {
	ret = krb5_make_principal(context, &p2, NULL, name, "admin", NULL);
	krb5_free_principal(context, p1);
	if(ret != 0)
	    return ret;

	*client = p2;
	return 0;
    }

    *client = p1;

    return 0;
}