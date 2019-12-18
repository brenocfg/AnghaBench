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
struct option {struct dir_struct* value; } ;
struct dir_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  add_patterns_from_file (struct dir_struct*,char const*) ; 
 int exc_given ; 

__attribute__((used)) static int option_parse_exclude_from(const struct option *opt,
				     const char *arg, int unset)
{
	struct dir_struct *dir = opt->value;

	BUG_ON_OPT_NEG(unset);

	exc_given = 1;
	add_patterns_from_file(dir, arg);

	return 0;
}