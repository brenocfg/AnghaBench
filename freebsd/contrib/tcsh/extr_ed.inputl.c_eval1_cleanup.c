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
struct eval1_state {int /*<<< orphan*/  evalp; int /*<<< orphan*/  evalvec; } ;

/* Variables and functions */
 scalar_t__ doneinp ; 
 int /*<<< orphan*/  evalp ; 
 int /*<<< orphan*/  evalvec ; 

__attribute__((used)) static void
eval1_cleanup(void *xstate)
{
    struct eval1_state *state;

    state = xstate;
    evalvec = state->evalvec;
    evalp = state->evalp;
    doneinp = 0;
}