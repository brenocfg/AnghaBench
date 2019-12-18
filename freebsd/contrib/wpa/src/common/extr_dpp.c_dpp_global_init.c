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
struct dpp_global_config {int /*<<< orphan*/  process_conf_obj; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  msg_ctx; } ;
struct dpp_global {int /*<<< orphan*/  tcp_init; int /*<<< orphan*/  controllers; int /*<<< orphan*/  configurator; int /*<<< orphan*/  bootstrap; int /*<<< orphan*/  process_conf_obj; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 struct dpp_global* os_zalloc (int) ; 

struct dpp_global * dpp_global_init(struct dpp_global_config *config)
{
	struct dpp_global *dpp;

	dpp = os_zalloc(sizeof(*dpp));
	if (!dpp)
		return NULL;
	dpp->msg_ctx = config->msg_ctx;
#ifdef CONFIG_DPP2
	dpp->cb_ctx = config->cb_ctx;
	dpp->process_conf_obj = config->process_conf_obj;
#endif /* CONFIG_DPP2 */

	dl_list_init(&dpp->bootstrap);
	dl_list_init(&dpp->configurator);
#ifdef CONFIG_DPP2
	dl_list_init(&dpp->controllers);
	dl_list_init(&dpp->tcp_init);
#endif /* CONFIG_DPP2 */

	return dpp;
}