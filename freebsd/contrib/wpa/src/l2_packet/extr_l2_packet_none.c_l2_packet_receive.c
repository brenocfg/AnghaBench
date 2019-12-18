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
typedef  scalar_t__ u8 ;
struct l2_packet_data {int /*<<< orphan*/  rx_callback_ctx; int /*<<< orphan*/  (* rx_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static void l2_packet_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct l2_packet_data *l2 = eloop_ctx;
	u8 buf[2300];
	int res;

	/* TODO: receive frame (e.g., recv() using sock */
	buf[0] = 0;
	res = 0;

	l2->rx_callback(l2->rx_callback_ctx, NULL /* TODO: src addr */,
			buf, res);
}