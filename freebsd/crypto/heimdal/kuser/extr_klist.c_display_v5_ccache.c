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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int check_for_tgt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tickets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
display_v5_ccache (krb5_context context, krb5_ccache ccache,
		   int do_test, int do_verbose,
		   int do_flags, int do_hidden)
{
    krb5_error_code ret;
    krb5_principal principal;
    int exit_status = 0;


    ret = krb5_cc_get_principal (context, ccache, &principal);
    if (ret) {
	if(ret == ENOENT) {
	    if (!do_test)
		krb5_warnx(context, N_("No ticket file: %s", ""),
			   krb5_cc_get_name(context, ccache));
	    return 1;
	} else
	    krb5_err (context, 1, ret, "krb5_cc_get_principal");
    }
    if (do_test)
	exit_status = check_for_tgt (context, ccache, principal, NULL);
    else
	print_tickets (context, ccache, principal, do_verbose,
		       do_flags, do_hidden);

    ret = krb5_cc_close (context, ccache);
    if (ret)
	krb5_err (context, 1, ret, "krb5_cc_close");

    krb5_free_principal (context, principal);

    return exit_status;
}