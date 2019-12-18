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
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_principal principal;

    ret = krb5_init_context(&context);
    if (ret)
	errx(1, "krb5_init_context");

    ret = krb5_parse_name(context, "lha@SU.SE", &principal);
    if (ret)
	krb5_err(context, ret, 1, "krb5_parse_name");

    parse_file(context, principal, 0);
    parse_file(context, principal, 1);

    krb5_free_principal(context, principal);

    krb5_free_context(context);

    return 0;
}