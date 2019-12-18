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
struct nmreq_opt_csb {int dummy; } ;
struct TestContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_options (struct TestContext*) ; 
 int port_register_hwall_tx (struct TestContext*) ; 
 int push_csb_option (struct TestContext*,struct nmreq_opt_csb*) ; 
 int sync_kloop_eventfds (struct TestContext*) ; 

__attribute__((used)) static int
sync_kloop_eventfds_all_tx(struct TestContext *ctx)
{
	struct nmreq_opt_csb opt;
	int ret;

	ret = push_csb_option(ctx, &opt);
	if (ret != 0) {
		return ret;
	}

	ret = port_register_hwall_tx(ctx);
	if (ret != 0) {
		return ret;
	}
	clear_options(ctx);

	return sync_kloop_eventfds(ctx);
}