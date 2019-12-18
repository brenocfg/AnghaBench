#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  TYPE_3__* krb5_principal ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int krb5_boolean ;
struct TYPE_10__ {int /*<<< orphan*/  canonicalize; } ;
struct TYPE_7__ {int len; char** val; } ;
struct TYPE_8__ {scalar_t__ name_type; TYPE_1__ name_string; } ;
struct TYPE_9__ {TYPE_2__ name; } ;
typedef  TYPE_4__ KDCOptions ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ KRB5_NT_SRV_INST ; 
 scalar_t__ _krb5_get_host_realm_int (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static krb5_boolean
need_referral(krb5_context context, krb5_kdc_configuration *config,
	      const KDCOptions * const options, krb5_principal server,
	      krb5_realm **realms)
{
    const char *name;

    if(!options->canonicalize && server->name.name_type != KRB5_NT_SRV_INST)
	return FALSE;

    if (server->name.name_string.len == 1)
	name = server->name.name_string.val[0];
    else if (server->name.name_string.len > 1)
	name = server->name.name_string.val[1];
    else
	return FALSE;

    kdc_log(context, config, 0, "Searching referral for %s", name);

    return _krb5_get_host_realm_int(context, name, FALSE, realms) == 0;
}