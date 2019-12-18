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
typedef  int /*<<< orphan*/ * rtbl_t ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_deltat ;
struct TYPE_6__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_cc_cursor ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  COL_EXPIRES ; 
 int /*<<< orphan*/  COL_FLAGS ; 
 int /*<<< orphan*/  COL_ISSUED ; 
 int /*<<< orphan*/  COL_PRINCIPAL ; 
 scalar_t__ KRB5_CC_END ; 
 int /*<<< orphan*/  KRB5_TC_NOTICKET ; 
 char* N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_cc_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_friendly_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_cc_get_kdc_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_cc_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_get_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_next_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_cc_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_start_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_is_config_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  print_cred (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_cred_verbose (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rtbl_add_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_separator (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  unparse_time (int,char*,int) ; 

__attribute__((used)) static void
print_tickets (krb5_context context,
	       krb5_ccache ccache,
	       krb5_principal principal,
	       int do_verbose,
	       int do_flags,
	       int do_hidden)
{
    krb5_error_code ret;
    char *str, *name;
    krb5_cc_cursor cursor;
    krb5_creds creds;
    krb5_deltat sec;

    rtbl_t ct = NULL;

    ret = krb5_unparse_name (context, principal, &str);
    if (ret)
	krb5_err (context, 1, ret, "krb5_unparse_name");

    printf ("%17s: %s:%s\n",
	    N_("Credentials cache", ""),
	    krb5_cc_get_type(context, ccache),
	    krb5_cc_get_name(context, ccache));
    printf ("%17s: %s\n", N_("Principal", ""), str);

    ret = krb5_cc_get_friendly_name(context, ccache, &name);
    if (ret == 0) {
	if (strcmp(name, str) != 0)
	    printf ("%17s: %s\n", N_("Friendly name", ""), name);
	free(name);
    }
    free (str);

    if(do_verbose) {
	printf ("%17s: %d\n", N_("Cache version", ""),
		krb5_cc_get_version(context, ccache));
    } else {
        krb5_cc_set_flags(context, ccache, KRB5_TC_NOTICKET);
    }

    ret = krb5_cc_get_kdc_offset(context, ccache, &sec);

    if (ret == 0 && do_verbose && sec != 0) {
	char buf[BUFSIZ];
	int val;
	int sig;

	val = sec;
	sig = 1;
	if (val < 0) {
	    sig = -1;
	    val = -val;
	}

	unparse_time (val, buf, sizeof(buf));

	printf ("%17s: %s%s\n", N_("KDC time offset", ""),
		sig == -1 ? "-" : "", buf);
    }

    printf("\n");

    ret = krb5_cc_start_seq_get (context, ccache, &cursor);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_start_seq_get");

    if(!do_verbose) {
	ct = rtbl_create();
	rtbl_add_column(ct, COL_ISSUED, 0);
	rtbl_add_column(ct, COL_EXPIRES, 0);
	if(do_flags)
	    rtbl_add_column(ct, COL_FLAGS, 0);
	rtbl_add_column(ct, COL_PRINCIPAL, 0);
	rtbl_set_separator(ct, "  ");
    }
    while ((ret = krb5_cc_next_cred (context,
				     ccache,
				     &cursor,
				     &creds)) == 0) {
	if (!do_hidden && krb5_is_config_principal(context, creds.server)) {
	    ;
	}else if(do_verbose){
	    print_cred_verbose(context, &creds);
	}else{
	    print_cred(context, &creds, ct, do_flags);
	}
	krb5_free_cred_contents (context, &creds);
    }
    if(ret != KRB5_CC_END)
	krb5_err(context, 1, ret, "krb5_cc_get_next");
    ret = krb5_cc_end_seq_get (context, ccache, &cursor);
    if (ret)
	krb5_err (context, 1, ret, "krb5_cc_end_seq_get");
    if(!do_verbose) {
	rtbl_format(ct, stdout);
	rtbl_destroy(ct);
    }
}