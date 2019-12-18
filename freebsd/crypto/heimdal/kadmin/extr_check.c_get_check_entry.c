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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_rec ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ kadm5_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_check_entry(const char *name, kadm5_principal_ent_rec *ent)
{
    krb5_error_code ret;
    krb5_principal principal;

    ret = krb5_parse_name(context, name, &principal);
    if (ret) {
	krb5_warn(context, ret, "krb5_unparse_name: %s", name);
	return 1;
    }

    memset(ent, 0, sizeof(*ent));
    ret = kadm5_get_principal(kadm_handle, principal, ent, 0);
    krb5_free_principal(context, principal);
    if(ret)
	return 1;

    return 0;
}