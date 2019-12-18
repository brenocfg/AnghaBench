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
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_init_vs_destroy(krb5_context context, const char *type)
{
    krb5_error_code ret;
    krb5_ccache id, id2;
    krb5_principal p, p2;
    char *n = NULL;

    ret = krb5_parse_name(context, "lha@SU.SE", &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_cc_new_unique(context, type, NULL, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_new_unique: %s", type);

    if (asprintf(&n, "%s:%s",
		 krb5_cc_get_type(context, id),
		 krb5_cc_get_name(context, id)) < 0 || n == NULL)
	errx(1, "malloc");


    ret = krb5_cc_resolve(context, n, &id2);
    free(n);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_resolve");

    krb5_cc_destroy(context, id);

    ret = krb5_cc_initialize(context, id2, p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_initialize");

    ret = krb5_cc_get_principal(context, id2, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_get_principal");

    krb5_cc_destroy(context, id2);
    krb5_free_principal(context, p);
    krb5_free_principal(context, p2);
}