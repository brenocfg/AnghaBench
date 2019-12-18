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
struct option {struct diff_options* value; } ;
struct diff_options {int filter; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 size_t DIFF_STATUS_FILTER_AON ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  diff_status_letters ; 
 int error (int /*<<< orphan*/ ,char const,char const*) ; 
 unsigned int* filter_bit ; 
 int /*<<< orphan*/  prepare_filter_bits () ; 
 int toupper (int) ; 

__attribute__((used)) static int diff_opt_diff_filter(const struct option *option,
				const char *optarg, int unset)
{
	struct diff_options *opt = option->value;
	int i, optch;

	BUG_ON_OPT_NEG(unset);
	prepare_filter_bits();

	/*
	 * If there is a negation e.g. 'd' in the input, and we haven't
	 * initialized the filter field with another --diff-filter, start
	 * from full set of bits, except for AON.
	 */
	if (!opt->filter) {
		for (i = 0; (optch = optarg[i]) != '\0'; i++) {
			if (optch < 'a' || 'z' < optch)
				continue;
			opt->filter = (1 << (ARRAY_SIZE(diff_status_letters) - 1)) - 1;
			opt->filter &= ~filter_bit[DIFF_STATUS_FILTER_AON];
			break;
		}
	}

	for (i = 0; (optch = optarg[i]) != '\0'; i++) {
		unsigned int bit;
		int negate;

		if ('a' <= optch && optch <= 'z') {
			negate = 1;
			optch = toupper(optch);
		} else {
			negate = 0;
		}

		bit = (0 <= optch && optch <= 'Z') ? filter_bit[optch] : 0;
		if (!bit)
			return error(_("unknown change class '%c' in --diff-filter=%s"),
				     optarg[i], optarg);
		if (negate)
			opt->filter &= ~bit;
		else
			opt->filter |= bit;
	}
	return 0;
}