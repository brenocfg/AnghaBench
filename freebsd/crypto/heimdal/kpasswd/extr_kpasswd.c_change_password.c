#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pwbuf ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {scalar_t__ length; scalar_t__ data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ UI_UTIL_read_pw_string (char*,int,char*,int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 char* krb5_passwd_result_to_string (int /*<<< orphan*/ ,int) ; 
 scalar_t__ krb5_set_password_using_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,char*) ; 

__attribute__((used)) static int
change_password(krb5_context context,
		krb5_principal principal,
		krb5_ccache id)
{
    krb5_data result_code_string, result_string;
    int result_code;
    krb5_error_code ret;
    char pwbuf[BUFSIZ];
    char *msg, *name;

    krb5_data_zero (&result_code_string);
    krb5_data_zero (&result_string);

    name = msg = NULL;
    if (principal == NULL)
	asprintf(&msg, "New password: ");
    else {
	ret = krb5_unparse_name(context, principal, &name);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_unparse_name");

	asprintf(&msg, "New password for %s: ", name);
    }

    if (msg == NULL)
	krb5_errx (context, 1, "out of memory");

    ret = UI_UTIL_read_pw_string (pwbuf, sizeof(pwbuf), msg, 1);
    free(msg);
    if (name)
	free(name);
    if (ret != 0) {
	return 1;
    }

    ret = krb5_set_password_using_ccache (context, id, pwbuf,
					  principal,
					  &result_code,
					  &result_code_string,
					  &result_string);
    if (ret) {
	krb5_warn (context, ret, "krb5_set_password_using_ccache");
	return 1;
    }

    printf ("%s%s%.*s\n", krb5_passwd_result_to_string(context, result_code),
	    result_string.length > 0 ? " : " : "",
	    (int)result_string.length,
	    result_string.length > 0 ? (char *)result_string.data : "");

    krb5_data_free (&result_code_string);
    krb5_data_free (&result_string);

    return ret != 0;
}