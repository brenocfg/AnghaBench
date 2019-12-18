#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ help_flag ; 
 scalar_t__ kadm5_add_passwd_quality_verifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* kadm5_check_password_quality (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kadm5_setup_passwd_quality_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_program_setup (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_std_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/ * password ; 
 char const* principal ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_principal p;
    const char *s;
    krb5_data pw_data;

    krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help_flag)
	krb5_std_usage(0, args, num_args);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    if (principal == NULL)
	krb5_errx(context, 1, "no principal given");
    if (password == NULL)
	krb5_errx(context, 1, "no password given");

    ret = krb5_parse_name(context, principal, &p);
    if (ret)
	krb5_errx(context, 1, "krb5_parse_name: %s", principal);

    pw_data.data = password;
    pw_data.length = strlen(password);

    kadm5_setup_passwd_quality_check (context, NULL, NULL);
    ret = kadm5_add_passwd_quality_verifier(context, NULL);
    if (ret)
	krb5_errx(context, 1, "kadm5_add_passwd_quality_verifier");

    s = kadm5_check_password_quality (context, p, &pw_data);
    if (s)
	krb5_errx(context, 1, "kadm5_check_password_quality:\n%s", s);

    krb5_free_principal(context, p);
    krb5_free_context(context);

    return 0;
}