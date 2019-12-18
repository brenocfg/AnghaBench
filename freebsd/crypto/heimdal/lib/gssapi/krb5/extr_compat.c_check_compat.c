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
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;
typedef  int /*<<< orphan*/  krb5_boolean ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  krb5_config_free_strings (char**) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_principal_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
check_compat(OM_uint32 *minor_status,
	     krb5_context context, krb5_const_principal name,
	     const char *option, krb5_boolean *compat,
	     krb5_boolean match_val)
{
    krb5_error_code ret = 0;
    char **p, **q;
    krb5_principal match;


    p = krb5_config_get_strings(context, NULL, "gssapi",
				option, NULL);
    if(p == NULL)
	return 0;

    match = NULL;
    for(q = p; *q; q++) {
	ret = krb5_parse_name(context, *q, &match);
	if (ret)
	    break;

	if (krb5_principal_match(context, name, match)) {
	    *compat = match_val;
	    break;
	}

	krb5_free_principal(context, match);
	match = NULL;
    }
    if (match)
	krb5_free_principal(context, match);
    krb5_config_free_strings(p);

    if (ret) {
	if (minor_status)
	    *minor_status = ret;
	return GSS_S_FAILURE;
    }

    return 0;
}