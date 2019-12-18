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
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int
not_found(krb5_context context, krb5_const_principal p, krb5_error_code code)
{
    krb5_error_code ret;
    char *str;

    ret = krb5_unparse_name(context, p, &str);
    if(ret) {
	krb5_clear_error_message(context);
	return code;
    }
    krb5_set_error_message(context, code,
			   N_("Matching credential (%s) not found", ""), str);
    free(str);
    return code;
}