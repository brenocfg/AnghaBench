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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  rtbl_t ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_cc_cache_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  COL_CACHENAME ; 
 int /*<<< orphan*/  COL_DEFCACHE ; 
 int /*<<< orphan*/  COL_EXPIRES ; 
 int /*<<< orphan*/  COL_NAME ; 
 scalar_t__ KRB5_CC_NOSUPP ; 
 char* N_ (char*,char*) ; 
 int check_for_tgt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_cc_cache_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_cache_get_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_cache_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_cc_default_name (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_friendly_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ krb5_cc_get_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_xfree (char*) ; 
 char* printable_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_column_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtbl_set_prefix (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
list_caches(krb5_context context)
{
    krb5_cc_cache_cursor cursor;
    const char *cdef_name;
    char *def_name;
    krb5_error_code ret;
    krb5_ccache id;
    rtbl_t ct;

    cdef_name = krb5_cc_default_name(context);
    if (cdef_name == NULL)
	krb5_errx(context, 1, "krb5_cc_default_name");
    def_name = strdup(cdef_name);

    ret = krb5_cc_cache_get_first (context, NULL, &cursor);
    if (ret == KRB5_CC_NOSUPP)
	return 0;
    else if (ret)
	krb5_err (context, 1, ret, "krb5_cc_cache_get_first");

    ct = rtbl_create();
    rtbl_add_column(ct, COL_NAME, 0);
    rtbl_add_column(ct, COL_CACHENAME, 0);
    rtbl_add_column(ct, COL_EXPIRES, 0);
    rtbl_add_column(ct, COL_DEFCACHE, 0);
    rtbl_set_prefix(ct, "   ");
    rtbl_set_column_prefix(ct, COL_NAME, "");

    while (krb5_cc_cache_next (context, cursor, &id) == 0) {
	krb5_principal principal = NULL;
	int expired = 0;
	char *name;
	time_t t;

	ret = krb5_cc_get_principal(context, id, &principal);
	if (ret)
	    continue;

	expired = check_for_tgt (context, id, principal, &t);

	ret = krb5_cc_get_friendly_name(context, id, &name);
	if (ret == 0) {
	    const char *str;
	    char *fname;
	    rtbl_add_column_entry(ct, COL_NAME, name);
	    rtbl_add_column_entry(ct, COL_CACHENAME,
				  krb5_cc_get_name(context, id));
	    if (expired)
		str = N_(">>> Expired <<<", "");
	    else
		str = printable_time(t);
	    rtbl_add_column_entry(ct, COL_EXPIRES, str);
	    free(name);

	    ret = krb5_cc_get_full_name(context, id, &fname);
	    if (ret)
		krb5_err (context, 1, ret, "krb5_cc_get_full_name");

	    if (strcmp(fname, def_name) == 0)
		rtbl_add_column_entry(ct, COL_DEFCACHE, "*");
	    else
		rtbl_add_column_entry(ct, COL_DEFCACHE, "");

	    krb5_xfree(fname);
	}
	krb5_cc_close(context, id);

	krb5_free_principal(context, principal);
    }

    krb5_cc_cache_end_seq_get(context, cursor);

    free(def_name);
    rtbl_format(ct, stdout);
    rtbl_destroy(ct);

    return 0;
}