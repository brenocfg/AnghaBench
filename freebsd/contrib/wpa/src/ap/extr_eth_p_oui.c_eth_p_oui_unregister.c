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
struct eth_p_oui_iface {int /*<<< orphan*/  l2; int /*<<< orphan*/  list; int /*<<< orphan*/  receiver; struct eth_p_oui_iface* iface; } ;
struct eth_p_oui_ctx {int /*<<< orphan*/  l2; int /*<<< orphan*/  list; int /*<<< orphan*/  receiver; struct eth_p_oui_ctx* iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct eth_p_oui_iface*) ; 

void eth_p_oui_unregister(struct eth_p_oui_ctx *ctx)
{
	struct eth_p_oui_iface *iface;

	if (!ctx)
		return;

	iface = ctx->iface;

	dl_list_del(&ctx->list);
	os_free(ctx);

	if (dl_list_empty(&iface->receiver)) {
		dl_list_del(&iface->list);
		l2_packet_deinit(iface->l2);
		os_free(iface);
	}
}