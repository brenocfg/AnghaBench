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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_PRINCIPAL_PARSE_ENTERPRISE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_set_default_realm (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
test_enterprise(krb5_context context)
{
    krb5_error_code ret;
    char *unparsed;
    krb5_principal p;

    ret = krb5_set_default_realm(context, "SAMBA.ORG");
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_parse_name_flags(context, "lha@su.se@WIN.SU.SE",
				KRB5_PRINCIPAL_PARSE_ENTERPRISE, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name_flags");

    ret = krb5_unparse_name(context, p, &unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name");

    krb5_free_principal(context, p);

    if (strcmp(unparsed, "lha\\@su.se@WIN.SU.SE") != 0)
	krb5_errx(context, 1, "enterprise name failed 1");
    free(unparsed);

    /*
     *
     */

    ret = krb5_parse_name_flags(context, "lha\\@su.se@WIN.SU.SE",
				KRB5_PRINCIPAL_PARSE_ENTERPRISE, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name_flags");

    ret = krb5_unparse_name(context, p, &unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name");

    krb5_free_principal(context, p);
    if (strcmp(unparsed, "lha\\@su.se\\@WIN.SU.SE@SAMBA.ORG") != 0)
	krb5_errx(context, 1, "enterprise name failed 2: %s", unparsed);
    free(unparsed);

    /*
     *
     */

    ret = krb5_parse_name_flags(context, "lha\\@su.se@WIN.SU.SE", 0, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name_flags");

    ret = krb5_unparse_name(context, p, &unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name");

    krb5_free_principal(context, p);
    if (strcmp(unparsed, "lha\\@su.se@WIN.SU.SE") != 0)
	krb5_errx(context, 1, "enterprise name failed 3");
    free(unparsed);

    /*
     *
     */

    ret = krb5_parse_name_flags(context, "lha@su.se",
				KRB5_PRINCIPAL_PARSE_ENTERPRISE, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name_flags");

    ret = krb5_unparse_name(context, p, &unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name");

    krb5_free_principal(context, p);
    if (strcmp(unparsed, "lha\\@su.se@SAMBA.ORG") != 0)
	krb5_errx(context, 1, "enterprise name failed 2: %s", unparsed);
    free(unparsed);
}