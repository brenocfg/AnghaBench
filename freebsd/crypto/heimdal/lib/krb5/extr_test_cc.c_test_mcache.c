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
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* krb5_cc_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_mcache(krb5_context context)
{
    krb5_error_code ret;
    krb5_ccache id, id2;
    const char *nc, *tc;
    char *c;
    krb5_principal p, p2;

    ret = krb5_parse_name(context, "lha@SU.SE", &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_new_unique");

    ret = krb5_cc_initialize(context, id, p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_initialize");

    nc = krb5_cc_get_name(context, id);
    if (nc == NULL)
	krb5_errx(context, 1, "krb5_cc_get_name");

    tc = krb5_cc_get_type(context, id);
    if (tc == NULL)
	krb5_errx(context, 1, "krb5_cc_get_name");

    if (asprintf(&c, "%s:%s", tc, nc) < 0 || c == NULL)
	errx(1, "malloc");

    krb5_cc_close(context, id);

    ret = krb5_cc_resolve(context, c, &id2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_resolve");

    ret = krb5_cc_get_principal(context, id2, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_get_principal");

    if (krb5_principal_compare(context, p, p2) == FALSE)
	krb5_errx(context, 1, "p != p2");

    krb5_cc_destroy(context, id2);
    krb5_free_principal(context, p);
    krb5_free_principal(context, p2);

    ret = krb5_cc_resolve(context, c, &id2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_resolve");

    ret = krb5_cc_get_principal(context, id2, &p2);
    if (ret == 0)
	krb5_errx(context, 1, "krb5_cc_get_principal");

    krb5_cc_destroy(context, id2);
    free(c);
}