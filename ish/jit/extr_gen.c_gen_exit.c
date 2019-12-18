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
struct gen_state {unsigned long ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen (struct gen_state*,unsigned long) ; 

void gen_exit(struct gen_state *state) {
    extern void gadget_exit(void);
    // in case the last instruction didn't end the block
    gen(state, (unsigned long) gadget_exit);
    gen(state, state->ip);
}