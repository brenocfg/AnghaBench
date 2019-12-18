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
struct get_options {int long_flag; int short_flag; int terse_flag; int /*<<< orphan*/ * column_info_string; } ;
struct get_entry_data {int /*<<< orphan*/ * table; int /*<<< orphan*/  format; scalar_t__ extra_mask; scalar_t__ mask; int /*<<< orphan*/ * chead; int /*<<< orphan*/ ** ctail; } ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/ * DEFAULT_COLUMNS_LONG ; 
 int /*<<< orphan*/ * DEFAULT_COLUMNS_SHORT ; 
 int /*<<< orphan*/  do_get_entry ; 
 scalar_t__ foreach_principal (char*,int /*<<< orphan*/ ,char const*,struct get_entry_data*) ; 
 int /*<<< orphan*/  free_columns (struct get_entry_data*) ; 
 int listit (char const*,int,char**) ; 
 int /*<<< orphan*/  print_entry_long ; 
 int /*<<< orphan*/  print_entry_short ; 
 int /*<<< orphan*/ * rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_separator (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ setup_columns (struct get_entry_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
getit(struct get_options *opt, const char *name, int argc, char **argv)
{
    int i;
    krb5_error_code ret;
    struct get_entry_data data;

    if(opt->long_flag == -1 && (opt->short_flag == 1 || opt->terse_flag == 1))
	opt->long_flag = 0;
    if(opt->short_flag == -1 && (opt->long_flag == 1 || opt->terse_flag == 1))
	opt->short_flag = 0;
    if(opt->terse_flag == -1 && (opt->long_flag == 1 || opt->short_flag == 1))
	opt->terse_flag = 0;
    if(opt->long_flag == 0 && opt->short_flag == 0 && opt->terse_flag == 0)
	opt->short_flag = 1;

    if (opt->terse_flag)
        return listit(name, argc, argv);

    data.table = NULL;
    data.chead = NULL;
    data.ctail = &data.chead;
    data.mask = 0;
    data.extra_mask = 0;

    if(opt->short_flag) {
	data.table = rtbl_create();
	rtbl_set_separator(data.table, "  ");
	data.format = print_entry_short;
    } else
	data.format = print_entry_long;
    if(opt->column_info_string == NULL) {
	if(opt->long_flag)
	    ret = setup_columns(&data, DEFAULT_COLUMNS_LONG);
	else
	    ret = setup_columns(&data, DEFAULT_COLUMNS_SHORT);
    } else
	ret = setup_columns(&data, opt->column_info_string);

    if(ret != 0) {
	if(data.table != NULL)
	    rtbl_destroy(data.table);
	return 0;
    }

    for(i = 0; i < argc; i++)
	ret = foreach_principal(argv[i], do_get_entry, name, &data);

    if(data.table != NULL) {
	rtbl_format(data.table, stdout);
	rtbl_destroy(data.table);
    }
    free_columns(&data);
    return ret != 0;
}