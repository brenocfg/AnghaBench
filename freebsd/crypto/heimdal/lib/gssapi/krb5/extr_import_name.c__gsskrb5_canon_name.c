#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_4__* krb5_const_principal ;
typedef  int /*<<< orphan*/  gss_name_t ;
struct TYPE_16__ {int /*<<< orphan*/  realm; } ;
struct TYPE_13__ {int len; char** val; } ;
struct TYPE_14__ {TYPE_1__ name_string; } ;
struct TYPE_15__ {TYPE_2__ name; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_BAD_NAME ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 scalar_t__ MAGIC_HOSTBASED_NAME_TYPE ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__**) ; 
 scalar_t__ krb5_principal_get_type (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ krb5_principal_set_realm (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_principal_set_type (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_sname_to_principal (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,TYPE_3__**) ; 

OM_uint32
_gsskrb5_canon_name(OM_uint32 *minor_status, krb5_context context,
		    int use_dns, krb5_const_principal sourcename, gss_name_t targetname,
		    krb5_principal *out)
{
    krb5_principal p = (krb5_principal)targetname;
    krb5_error_code ret;
    char *hostname = NULL, *service;

    *minor_status = 0;

    /* If its not a hostname */
    if (krb5_principal_get_type(context, p) != MAGIC_HOSTBASED_NAME_TYPE) {
	ret = krb5_copy_principal(context, p, out);
    } else if (!use_dns) {
	ret = krb5_copy_principal(context, p, out);
	if (ret)
	    goto out;
	krb5_principal_set_type(context, *out, KRB5_NT_SRV_HST);
	if (sourcename)
	    ret = krb5_principal_set_realm(context, *out, sourcename->realm);
    } else {
	if (p->name.name_string.len == 0)
	    return GSS_S_BAD_NAME;
	else if (p->name.name_string.len > 1)
	    hostname = p->name.name_string.val[1];

	service = p->name.name_string.val[0];

	ret = krb5_sname_to_principal(context,
				      hostname,
				      service,
				      KRB5_NT_SRV_HST,
				      out);
    }

 out:
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    return 0;
}