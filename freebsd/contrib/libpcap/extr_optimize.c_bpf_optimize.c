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
struct icode {int /*<<< orphan*/  root; } ;
typedef  int /*<<< orphan*/  opt_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  intern_blocks (int /*<<< orphan*/ *,struct icode*) ; 
 int /*<<< orphan*/  opt_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_dump (int /*<<< orphan*/ *,struct icode*) ; 
 int /*<<< orphan*/  opt_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct icode*) ; 
 int /*<<< orphan*/  opt_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct icode*,int) ; 
 int /*<<< orphan*/  opt_root (int /*<<< orphan*/ *) ; 
 int pcap_optimizer_debug ; 
 scalar_t__ pcap_print_dot_graph ; 
 int /*<<< orphan*/  printf (char*) ; 

void
bpf_optimize(compiler_state_t *cstate, struct icode *ic)
{
	opt_state_t opt_state;

	opt_init(cstate, &opt_state, ic);
	opt_loop(cstate, &opt_state, ic, 0);
	opt_loop(cstate, &opt_state, ic, 1);
	intern_blocks(&opt_state, ic);
#ifdef BDEBUG
	if (pcap_optimizer_debug > 1 || pcap_print_dot_graph) {
		printf("after intern_blocks()\n");
		opt_dump(cstate, ic);
	}
#endif
	opt_root(&ic->root);
#ifdef BDEBUG
	if (pcap_optimizer_debug > 1 || pcap_print_dot_graph) {
		printf("after opt_root()\n");
		opt_dump(cstate, ic);
	}
#endif
	opt_cleanup(&opt_state);
}