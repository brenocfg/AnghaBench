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
struct option {struct apply_state* value; } ;
struct apply_state {int p_value_known; int /*<<< orphan*/  p_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  atoi (char const*) ; 

__attribute__((used)) static int apply_option_parse_p(const struct option *opt,
				const char *arg,
				int unset)
{
	struct apply_state *state = opt->value;

	BUG_ON_OPT_NEG(unset);

	state->p_value = atoi(arg);
	state->p_value_known = 1;
	return 0;
}