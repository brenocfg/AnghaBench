#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct icode {int /*<<< orphan*/  root; } ;
struct TYPE_9__ {int done; } ;
typedef  TYPE_1__ opt_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  find_closure (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_dom (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_edom (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_levels (TYPE_1__*,struct icode*) ; 
 int /*<<< orphan*/  find_ud (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_blks (int /*<<< orphan*/ *,TYPE_1__*,struct icode*,int) ; 
 int /*<<< orphan*/  opt_dump (int /*<<< orphan*/ *,struct icode*) ; 
 int pcap_optimizer_debug ; 
 scalar_t__ pcap_print_dot_graph ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
opt_loop(compiler_state_t *cstate, opt_state_t *opt_state, struct icode *ic,
    int do_stmts)
{

#ifdef BDEBUG
	if (pcap_optimizer_debug > 1 || pcap_print_dot_graph) {
		printf("opt_loop(root, %d) begin\n", do_stmts);
		opt_dump(cstate, ic);
	}
#endif
	do {
		opt_state->done = 1;
		find_levels(opt_state, ic);
		find_dom(opt_state, ic->root);
		find_closure(opt_state, ic->root);
		find_ud(opt_state, ic->root);
		find_edom(opt_state, ic->root);
		opt_blks(cstate, opt_state, ic, do_stmts);
#ifdef BDEBUG
		if (pcap_optimizer_debug > 1 || pcap_print_dot_graph) {
			printf("opt_loop(root, %d) bottom, done=%d\n", do_stmts, opt_state->done);
			opt_dump(cstate, ic);
		}
#endif
	} while (!opt_state->done);
}