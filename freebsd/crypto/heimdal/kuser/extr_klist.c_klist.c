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
struct klist_options {scalar_t__ verbose_flag; scalar_t__ v5_flag; scalar_t__ tokens_flag; int /*<<< orphan*/  hidden_flag; int /*<<< orphan*/  flags_flag; int /*<<< orphan*/  cache_string; scalar_t__ all_content_flag; scalar_t__ list_all_flag; scalar_t__ s_flag; scalar_t__ test_flag; scalar_t__ n_flag; scalar_t__ a_flag; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_cc_cache_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  display_tokens (scalar_t__) ; 
 int display_v5_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ k_hasafs () ; 
 int /*<<< orphan*/  kcc_context ; 
 int /*<<< orphan*/  krb5_cc_cache_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_cache_get_first (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_cache_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,...) ; 
 int list_caches (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
klist(struct klist_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    int exit_status = 0;

    int do_verbose =
	opt->verbose_flag ||
	opt->a_flag ||
	opt->n_flag;
    int do_test =
	opt->test_flag ||
	opt->s_flag;

    if (opt->list_all_flag) {
	exit_status = list_caches(kcc_context);
	return exit_status;
    }

    if (opt->v5_flag) {
	krb5_ccache id;

	if (opt->all_content_flag) {
	    krb5_cc_cache_cursor cursor;

	    ret = krb5_cc_cache_get_first(kcc_context, NULL, &cursor);
	    if (ret)
		krb5_err(kcc_context, 1, ret, "krb5_cc_cache_get_first");


	    while (krb5_cc_cache_next(kcc_context, cursor, &id) == 0) {
		exit_status |= display_v5_ccache(kcc_context, id, do_test,
						 do_verbose, opt->flags_flag,
						 opt->hidden_flag);
		printf("\n\n");
	    }
	    krb5_cc_cache_end_seq_get(kcc_context, cursor);

	} else {
	    if(opt->cache_string) {
		ret = krb5_cc_resolve(kcc_context, opt->cache_string, &id);
		if (ret)
		    krb5_err(kcc_context, 1, ret, "%s", opt->cache_string);
	    } else {
		ret = krb5_cc_default(kcc_context, &id);
		if (ret)
		    krb5_err(kcc_context, 1, ret, "krb5_cc_resolve");
	    }
	    exit_status = display_v5_ccache(kcc_context, id, do_test,
					    do_verbose, opt->flags_flag,
					    opt->hidden_flag);
	}
    }

    if (!do_test) {
#ifndef NO_AFS
	if (opt->tokens_flag && k_hasafs()) {
	    if (opt->v5_flag)
		printf("\n");
	    display_tokens(opt->verbose_flag);
	}
#endif
    }

    return exit_status;
}