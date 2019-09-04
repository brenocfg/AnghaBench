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
struct apply_state {scalar_t__ apply; int /*<<< orphan*/  ws_error_action; int /*<<< orphan*/  whitespace_option; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_default_whitespace ; 
 int /*<<< orphan*/  nowarn_ws_error ; 
 int /*<<< orphan*/  warn_on_ws_error ; 

__attribute__((used)) static void set_default_whitespace_mode(struct apply_state *state)
{
	if (!state->whitespace_option && !apply_default_whitespace)
		state->ws_error_action = (state->apply ? warn_on_ws_error : nowarn_ws_error);
}