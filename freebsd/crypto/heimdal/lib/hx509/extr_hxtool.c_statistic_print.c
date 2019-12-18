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
struct statistic_print_options {int type_integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  hx509_query_unparse_stats (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stat_file_string ; 
 int /*<<< orphan*/  stdout ; 

int
statistic_print(struct statistic_print_options*opt, int argc, char **argv)
{
    int type = 0;

    if (stat_file_string == NULL)
	errx(1, "no stat file");

    if (opt->type_integer)
	type = opt->type_integer;

    hx509_query_unparse_stats(context, type, stdout);
    return 0;
}