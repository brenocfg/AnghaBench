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
struct apply_state {int /*<<< orphan*/  linenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  record_ws_error (struct apply_state*,unsigned int,char const*,int,int /*<<< orphan*/ ) ; 
 unsigned int ws_check (char const*,int,unsigned int) ; 

__attribute__((used)) static void check_whitespace(struct apply_state *state,
			     const char *line,
			     int len,
			     unsigned ws_rule)
{
	unsigned result = ws_check(line + 1, len - 1, ws_rule);

	record_ws_error(state, result, line + 1, len - 2, state->linenr);
}