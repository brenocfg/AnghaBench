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
typedef  int /*<<< orphan*/  localname ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_realm ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_aname_to_localname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void
test_alname(krb5_context context, krb5_const_realm realm,
	    const char *user, const char *inst,
	    const char *localuser, int ok)
{
    krb5_principal p;
    char localname[1024];
    krb5_error_code ret;
    char *princ;

    ret = krb5_make_principal(context, &p, realm, user, inst, NULL);
    if (ret)
	krb5_err(context, 1, ret, "krb5_build_principal");

    ret = krb5_unparse_name(context, p, &princ);
    if (ret)
	krb5_err(context, 1, ret, "krb5_unparse_name");

    ret = krb5_aname_to_localname(context, p, sizeof(localname), localname);
    krb5_free_principal(context, p);
    free(princ);
    if (ret) {
	if (!ok)
	    return;
	krb5_err(context, 1, ret, "krb5_aname_to_localname: %s -> %s",
		 princ, localuser);
    }

    if (strcmp(localname, localuser) != 0) {
	if (ok)
	    errx(1, "compared failed %s != %s (should have succeded)",
		 localname, localuser);
    } else {
	if (!ok)
	    errx(1, "compared failed %s == %s (should have failed)",
		 localname, localuser);
    }

}