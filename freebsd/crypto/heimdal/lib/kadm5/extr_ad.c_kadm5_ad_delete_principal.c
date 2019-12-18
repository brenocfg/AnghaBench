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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int kadm5_ret_t ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_ad_context ;

/* Variables and functions */
 int /*<<< orphan*/  CTX2LP (TYPE_1__*) ; 
 int KADM5_RPC_ERROR ; 
 int KADM5_UNK_PRINC ; 
 int _kadm5_ad_connect (void*) ; 
 scalar_t__ ad_find_entry (TYPE_1__*,char const*,char*,char**) ; 
 int ad_get_cred (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ check_ldap (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_fqdn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 int krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int ldap_delete_s (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_ad_delete_principal(void *server_handle, krb5_principal principal)
{
    kadm5_ad_context *context = server_handle;
#ifdef OPENLDAP
    char *p, *dn = NULL;
    const char *fqdn;
    int ret;

    ret = ad_get_cred(context, NULL);
    if (ret)
	return ret;

    ret = _kadm5_ad_connect(server_handle);
    if (ret)
	return ret;

    fqdn = get_fqdn(context->context, principal);

    ret = krb5_unparse_name(context->context, principal, &p);
    if (ret)
	return ret;

    if (ad_find_entry(context, fqdn, p, &dn) != 0) {
	free(p);
	return KADM5_UNK_PRINC;
    }

    ret = ldap_delete_s(CTX2LP(context), dn);

    free(dn);
    free(p);

    if (check_ldap(context, ret))
	return KADM5_RPC_ERROR;
    return 0;
#else
    krb5_set_error_message(context->context, KADM5_RPC_ERROR, "Function not implemented");
    return KADM5_RPC_ERROR;
#endif
}