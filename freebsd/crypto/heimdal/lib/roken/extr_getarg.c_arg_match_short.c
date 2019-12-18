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
struct getargs {char short_name; scalar_t__ type; struct getarg_collect_info* value; } ;
struct getarg_collect_info {int /*<<< orphan*/  data; scalar_t__ (* func ) (int /*<<< orphan*/ ,int,char**,int*,int*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  getarg_strings ;

/* Variables and functions */
 int ARG_ERR_BAD_ARG ; 
 int ARG_ERR_NO_ARG ; 
 int ARG_ERR_NO_MATCH ; 
 int /*<<< orphan*/  TRUE ; 
 int add_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ arg_collect ; 
 scalar_t__ arg_counter ; 
 scalar_t__ arg_double ; 
 scalar_t__ arg_flag ; 
 scalar_t__ arg_integer ; 
 scalar_t__ arg_negative_flag ; 
 scalar_t__ arg_string ; 
 scalar_t__ arg_strings ; 
 int sscanf (char*,char*,...) ; 
 size_t strlen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,char**,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arg_match_short (struct getargs *args, size_t num_args,
		 char *argv, int argc, char **rargv, int *goptind)
{
    size_t j, k;

    for(j = 1; j > 0 && j < strlen(rargv[*goptind]); j++) {
	for(k = 0; k < num_args; k++) {
	    char *goptarg;

	    if(args[k].short_name == 0)
		continue;
	    if(argv[j] == args[k].short_name) {
		if(args[k].type == arg_flag) {
		    *(int*)args[k].value = 1;
		    break;
		}
		if(args[k].type == arg_negative_flag) {
		    *(int*)args[k].value = 0;
		    break;
		}
		if(args[k].type == arg_counter) {
		    ++*(int *)args[k].value;
		    break;
		}
		if(args[k].type == arg_collect) {
		    struct getarg_collect_info *c = args[k].value;
		    int a = (int)j;

		    if((*c->func)(TRUE, argc, rargv, goptind, &a, c->data))
			return ARG_ERR_BAD_ARG;
		    j = a;
		    break;
		}

		if(argv[j + 1])
		    goptarg = &argv[j + 1];
		else {
		    ++*goptind;
		    goptarg = rargv[*goptind];
		}
		if(goptarg == NULL) {
		    --*goptind;
		    return ARG_ERR_NO_ARG;
		}
		if(args[k].type == arg_integer) {
		    int tmp;
		    if(sscanf(goptarg, "%d", &tmp) != 1)
			return ARG_ERR_BAD_ARG;
		    *(int*)args[k].value = tmp;
		    return 0;
		} else if(args[k].type == arg_string) {
		    *(char**)args[k].value = goptarg;
		    return 0;
		} else if(args[k].type == arg_strings) {
		    return add_string((getarg_strings*)args[k].value, goptarg);
		} else if(args[k].type == arg_double) {
		    double tmp;
		    if(sscanf(goptarg, "%lf", &tmp) != 1)
			return ARG_ERR_BAD_ARG;
		    *(double*)args[k].value = tmp;
		    return 0;
		}
		return ARG_ERR_BAD_ARG;
	    }
	}
	if (k == num_args)
	    return ARG_ERR_NO_MATCH;
    }
    return 0;
}