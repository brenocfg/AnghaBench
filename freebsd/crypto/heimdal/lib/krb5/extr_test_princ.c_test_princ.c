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
 int /*<<< orphan*/  KRB5_PRINCIPAL_PARSE_NO_REALM ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_PARSE_REQUIRE_REALM ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_UNPARSE_DISPLAY ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_UNPARSE_NO_REALM ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_UNPARSE_SHORT ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name_flags (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_principal_compare_any_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_set_default_realm (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_unparse_name_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
test_princ(krb5_context context)
{
    const char *princ = "lha@SU.SE";
    const char *princ_short = "lha";
    const char *noquote;
    krb5_error_code ret;
    char *princ_unparsed;
    char *princ_reformed = NULL;
    const char *realm;

    krb5_principal p, p2;

    ret = krb5_parse_name(context, princ, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_unparse_name(context, p, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ, princ_unparsed)) {
	krb5_errx(context, 1, "%s != %s", princ, princ_unparsed);
    }

    free(princ_unparsed);

    ret = krb5_unparse_name_flags(context, p,
				  KRB5_PRINCIPAL_UNPARSE_NO_REALM,
				  &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ_short, princ_unparsed))
	krb5_errx(context, 1, "%s != %s", princ_short, princ_unparsed);
    free(princ_unparsed);

    realm = krb5_principal_get_realm(context, p);

    if (asprintf(&princ_reformed, "%s@%s", princ_short, realm) < 0 || princ_reformed == NULL)
	errx(1, "malloc");

    ret = krb5_parse_name(context, princ_reformed, &p2);
    free(princ_reformed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (!krb5_principal_compare(context, p, p2)) {
	krb5_errx(context, 1, "p != p2");
    }

    krb5_free_principal(context, p2);

    ret = krb5_set_default_realm(context, "SU.SE");
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_unparse_name_flags(context, p,
				  KRB5_PRINCIPAL_UNPARSE_SHORT,
				  &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ_short, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ_short, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_parse_name(context, princ_short, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (!krb5_principal_compare(context, p, p2))
	krb5_errx(context, 1, "p != p2");
    krb5_free_principal(context, p2);

    ret = krb5_unparse_name(context, p, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_set_default_realm(context, "SAMBA.ORG");
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_parse_name(context, princ_short, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (krb5_principal_compare(context, p, p2))
	krb5_errx(context, 1, "p == p2");

    if (!krb5_principal_compare_any_realm(context, p, p2))
	krb5_errx(context, 1, "(ignoring realms) p != p2");

    ret = krb5_unparse_name(context, p2, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ, princ_unparsed) == 0)
	krb5_errx(context, 1, "%s == %s", princ, princ_unparsed);
    free(princ_unparsed);

    krb5_free_principal(context, p2);

    ret = krb5_parse_name(context, princ, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (!krb5_principal_compare(context, p, p2))
	krb5_errx(context, 1, "p != p2");

    ret = krb5_unparse_name(context, p2, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (strcmp(princ, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ, princ_unparsed);
    free(princ_unparsed);

    krb5_free_principal(context, p2);

    ret = krb5_unparse_name_flags(context, p,
				  KRB5_PRINCIPAL_UNPARSE_SHORT,
				  &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_short");

    if (strcmp(princ, princ_unparsed) != 0)
	krb5_errx(context, 1, "'%s' != '%s'", princ, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_unparse_name(context, p, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_short");

    if (strcmp(princ, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_parse_name_flags(context, princ,
				KRB5_PRINCIPAL_PARSE_NO_REALM,
				&p2);
    if (!ret)
	krb5_err(context, 1, ret, "Should have failed to parse %s a "
		 "short name", princ);

    ret = krb5_parse_name_flags(context, princ_short,
				KRB5_PRINCIPAL_PARSE_NO_REALM,
				&p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_unparse_name_flags(context, p2,
				  KRB5_PRINCIPAL_UNPARSE_NO_REALM,
				  &princ_unparsed);
    krb5_free_principal(context, p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_norealm");

    if (strcmp(princ_short, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ_short, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_parse_name_flags(context, princ_short,
				KRB5_PRINCIPAL_PARSE_REQUIRE_REALM,
				&p2);
    if (!ret)
	krb5_err(context, 1, ret, "Should have failed to parse %s "
		 "because it lacked a realm", princ_short);

    ret = krb5_parse_name_flags(context, princ,
				KRB5_PRINCIPAL_PARSE_REQUIRE_REALM,
				&p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    if (!krb5_principal_compare(context, p, p2))
	krb5_errx(context, 1, "p != p2");

    ret = krb5_unparse_name_flags(context, p2,
				  KRB5_PRINCIPAL_UNPARSE_NO_REALM,
				  &princ_unparsed);
    krb5_free_principal(context, p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_norealm");

    if (strcmp(princ_short, princ_unparsed))
	krb5_errx(context, 1, "'%s' != '%s'", princ_short, princ_unparsed);
    free(princ_unparsed);

    krb5_free_principal(context, p);

    /* test quoting */

    princ = "test\\ principal@SU.SE";
    noquote = "test principal@SU.SE";

    ret = krb5_parse_name_flags(context, princ, 0, &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_unparse_name_flags(context, p, 0, &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_flags");

    if (strcmp(princ, princ_unparsed))
	krb5_errx(context, 1, "q '%s' != '%s'", princ, princ_unparsed);
    free(princ_unparsed);

    ret = krb5_unparse_name_flags(context, p, KRB5_PRINCIPAL_UNPARSE_DISPLAY,
				  &princ_unparsed);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name_flags");

    if (strcmp(noquote, princ_unparsed))
	krb5_errx(context, 1, "nq '%s' != '%s'", noquote, princ_unparsed);
    free(princ_unparsed);

    krb5_free_principal(context, p);
}