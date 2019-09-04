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
struct index_state {int dummy; } ;

/* Variables and functions */
 char* parse_loc (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char const* parse_range_funcname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct index_state*) ; 

const char *skip_range_arg(const char *arg, struct index_state *istate)
{
	if (*arg == ':' || (*arg == '^' && *(arg + 1) == ':'))
		return parse_range_funcname(arg, NULL, NULL,
					    0, 0, NULL, NULL,
					    NULL, istate);

	arg = parse_loc(arg, NULL, NULL, 0, -1, NULL);

	if (*arg == ',')
		arg = parse_loc(arg+1, NULL, NULL, 0, 0, NULL);

	return arg;
}