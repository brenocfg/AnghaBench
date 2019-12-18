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
struct kswitch_options {scalar_t__ cache_string; int /*<<< orphan*/  type_string; int /*<<< orphan*/  principal_string; scalar_t__ interactive_flag; } ;
typedef  int /*<<< orphan*/  rtbl_t ;
typedef  int /*<<< orphan*/  num ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
struct TYPE_3__ {int /*<<< orphan*/  prefix; } ;
typedef  TYPE_1__ krb5_cc_ops ;
typedef  int /*<<< orphan*/  krb5_cc_cache_cursor ;
typedef  int /*<<< orphan*/  ids ;

/* Variables and functions */
 char* N_ (char*,char*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/ ** erealloc (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kcc_context ; 
 int /*<<< orphan*/  krb5_cc_cache_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_cache_get_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_cache_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_cache_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* krb5_cc_get_prefix_ops (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* krb5_cc_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  rtbl_add_column_by_id (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column_entry_by_id (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_column_affix_by_id (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

int
kswitch(struct kswitch_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    krb5_ccache id = NULL;

    if (opt->cache_string && opt->principal_string)
	krb5_errx(kcc_context, 1,
		  N_("Both --cache and --principal given, choose one", ""));

    if (opt->interactive_flag) {
	krb5_cc_cache_cursor cursor;
	krb5_ccache *ids = NULL;
	size_t i, len = 0;
	char *name;
	rtbl_t ct;

	ct = rtbl_create();

	rtbl_add_column_by_id(ct, 0, "#", 0);
	rtbl_add_column_by_id(ct, 1, "Principal", 0);
	rtbl_set_column_affix_by_id(ct, 1, "    ", "");
        rtbl_add_column_by_id(ct, 2, "Type", 0);
        rtbl_set_column_affix_by_id(ct, 2, "  ", "");

	ret = krb5_cc_cache_get_first(kcc_context, NULL, &cursor);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "krb5_cc_cache_get_first");

	while (krb5_cc_cache_next(kcc_context, cursor, &id) == 0) {
	    krb5_principal p;
	    char num[10];

	    ret = krb5_cc_get_principal(kcc_context, id, &p);
	    if (ret)
		continue;

	    ret = krb5_unparse_name(kcc_context, p, &name);
	    krb5_free_principal(kcc_context, p);

	    snprintf(num, sizeof(num), "%d", (int)(len + 1));
	    rtbl_add_column_entry_by_id(ct, 0, num);
	    rtbl_add_column_entry_by_id(ct, 1, name);
            rtbl_add_column_entry_by_id(ct, 2, krb5_cc_get_type(kcc_context, id));
	    free(name);

	    ids = erealloc(ids, (len + 1) * sizeof(ids[0]));
	    ids[len] = id;
	    len++;
	}
	krb5_cc_cache_end_seq_get(kcc_context, cursor);

	rtbl_format(ct, stdout);
	rtbl_destroy(ct);

	name = readline("Select number: ");
	if (name) {
	    i = atoi(name);
	    if (i == 0)
		krb5_errx(kcc_context, 1, "Cache number '%s' is invalid", name);
	    if (i > len)
		krb5_errx(kcc_context, 1, "Cache number '%s' is too large", name);

	    id = ids[i - 1];
	    ids[i - 1] = NULL;
	} else
	    krb5_errx(kcc_context, 1, "No cache selected");
	for (i = 0; i < len; i++)
	    if (ids[i])
		krb5_cc_close(kcc_context, ids[i]);

    } else if (opt->principal_string) {
	krb5_principal p;

	ret = krb5_parse_name(kcc_context, opt->principal_string, &p);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "krb5_parse_name: %s",
		     opt->principal_string);

	ret = krb5_cc_cache_match(kcc_context, p, &id);
	if (ret)
	    krb5_err(kcc_context, 1, ret,
		     N_("Did not find principal: %s", ""),
		     opt->principal_string);

	krb5_free_principal(kcc_context, p);

    } else if (opt->cache_string) {
	const krb5_cc_ops *ops;
	char *str;

	ops = krb5_cc_get_prefix_ops(kcc_context, opt->type_string);
	if (ops == NULL)
	    krb5_err(kcc_context, 1, 0, "krb5_cc_get_prefix_ops");

	asprintf(&str, "%s:%s", ops->prefix, opt->cache_string);
	if (str == NULL)
	    krb5_errx(kcc_context, 1, N_("out of memory", ""));

	ret = krb5_cc_resolve(kcc_context, str, &id);
	if (ret)
	    krb5_err(kcc_context, 1, ret, "krb5_cc_resolve: %s", str);

	free(str);
    } else {
	krb5_errx(kcc_context, 1, "missing option for kswitch");
    }

    ret = krb5_cc_switch(kcc_context, id);
    if (ret)
	krb5_err(kcc_context, 1, ret, "krb5_cc_switch");

    return 0;
}