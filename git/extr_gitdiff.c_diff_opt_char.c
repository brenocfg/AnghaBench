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
struct option {char* value; int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int diff_opt_char(const struct option *opt,
			 const char *arg, int unset)
{
	char *value = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (arg[1])
		return error(_("%s expects a character, got '%s'"),
			     opt->long_name, arg);
	*value = arg[0];
	return 0;
}