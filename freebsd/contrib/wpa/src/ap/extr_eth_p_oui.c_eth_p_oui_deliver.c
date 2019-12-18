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
typedef  int /*<<< orphan*/  u8 ;
struct eth_p_oui_ctx {int /*<<< orphan*/  oui_suffix; int /*<<< orphan*/  rx_callback_ctx; int /*<<< orphan*/  (* rx_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

void eth_p_oui_deliver(struct eth_p_oui_ctx *ctx, const u8 *src_addr,
		       const u8 *dst_addr, const u8 *buf, size_t len)
{
	ctx->rx_callback(ctx->rx_callback_ctx, src_addr, dst_addr,
			 ctx->oui_suffix, buf, len);
}