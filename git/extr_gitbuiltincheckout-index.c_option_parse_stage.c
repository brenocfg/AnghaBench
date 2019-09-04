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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 char CHECKOUT_ALL ; 
 int /*<<< orphan*/  _ (char*) ; 
 char checkout_stage ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int to_tempfile ; 

__attribute__((used)) static int option_parse_stage(const struct option *opt,
			      const char *arg, int unset)
{
	BUG_ON_OPT_NEG(unset);

	if (!strcmp(arg, "all")) {
		to_tempfile = 1;
		checkout_stage = CHECKOUT_ALL;
	} else {
		int ch = arg[0];
		if ('1' <= ch && ch <= '3')
			checkout_stage = arg[0] - '0';
		else
			die(_("stage should be between 1 and 3 or all"));
	}
	return 0;
}