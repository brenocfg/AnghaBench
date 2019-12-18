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
typedef  char const* krb5_realm ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  krb5_free_host_realm (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ krb5_get_default_realms (int /*<<< orphan*/ ,char const***) ; 
 int /*<<< orphan*/ * krb5_principal_get_comp_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static krb5_boolean
match_local_principals(krb5_context context,
		       krb5_principal principal,
		       const char *luser)
{
    krb5_error_code ret;
    krb5_realm *realms, *r;
    krb5_boolean result = FALSE;

    /* multi-component principals can never match */
    if(krb5_principal_get_comp_string(context, principal, 1) != NULL)
	return FALSE;

    ret = krb5_get_default_realms (context, &realms);
    if (ret)
	return FALSE;

    for (r = realms; *r != NULL; ++r) {
	if(strcmp(krb5_principal_get_realm(context, principal),
		  *r) != 0)
	    continue;
	if(strcmp(krb5_principal_get_comp_string(context, principal, 0),
		  luser) == 0) {
	    result = TRUE;
	    break;
	}
    }
    krb5_free_host_realm (context, realms);
    return result;
}