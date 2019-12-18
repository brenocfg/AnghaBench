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
struct dpp_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpp_bootstrap_del (struct dpp_global*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_configurator_del (struct dpp_global*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_controller_stop (struct dpp_global*) ; 
 int /*<<< orphan*/  dpp_relay_flush_controllers (struct dpp_global*) ; 
 int /*<<< orphan*/  dpp_tcp_init_flush (struct dpp_global*) ; 

void dpp_global_clear(struct dpp_global *dpp)
{
	if (!dpp)
		return;

	dpp_bootstrap_del(dpp, 0);
	dpp_configurator_del(dpp, 0);
#ifdef CONFIG_DPP2
	dpp_tcp_init_flush(dpp);
	dpp_relay_flush_controllers(dpp);
	dpp_controller_stop(dpp);
#endif /* CONFIG_DPP2 */
}