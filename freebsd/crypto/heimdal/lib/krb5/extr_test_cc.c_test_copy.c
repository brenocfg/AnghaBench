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
 scalar_t__ krb5_cc_copy_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_copy(krb5_context context, const char *from, const char *to)
{
    krb5_ccache fromid, toid;
    krb5_error_code ret;
    krb5_principal p, p2;

    ret = krb5_parse_name(context, "lha@SU.SE", &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_cc_new_unique(context, from, NULL, &fromid);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_new_unique: %s", from);

    ret = krb5_cc_initialize(context, fromid, p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_initialize");

    ret = krb5_cc_new_unique(context, to, NULL, &toid);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_gen_new: %s", to);

    ret = krb5_cc_copy_cache(context, fromid, toid);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_copy_cache");

    ret = krb5_cc_get_principal(context, toid, &p2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_get_principal");

    if (krb5_principal_compare(context, p, p2) == FALSE)
	krb5_errx(context, 1, "p != p2");

    krb5_free_principal(context, p);
    krb5_free_principal(context, p2);

    krb5_cc_destroy(context, fromid);
    krb5_cc_destroy(context, toid);
}