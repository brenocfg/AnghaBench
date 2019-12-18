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
struct tellmewhat_s0_cleanup {int /*<<< orphan*/  val; int /*<<< orphan*/ * dest; } ;

/* Variables and functions */

__attribute__((used)) static void
tellmewhat_s0_cleanup(void *xstate)
{
    struct tellmewhat_s0_cleanup *state;

    state = xstate;
    *state->dest = state->val;
}