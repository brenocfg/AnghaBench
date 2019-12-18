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
struct TYPE_3__ {char* data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 char* kadm5_check_password_quality (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
password_quality(void *opt, int argc, char **argv)
{
    krb5_error_code ret;
    krb5_principal principal;
    krb5_data pw_data;
    const char *s;

    ret = krb5_parse_name(context, argv[0], &principal);
    if(ret){
	krb5_warn(context, ret, "krb5_parse_name(%s)", argv[0]);
	return 0;
    }
    pw_data.data = argv[1];
    pw_data.length = strlen(argv[1]);

    s = kadm5_check_password_quality (context, principal, &pw_data);
    if (s)
	krb5_warnx(context, "kadm5_check_password_quality: %s", s);

    krb5_free_principal(context, principal);

    return 0;
}