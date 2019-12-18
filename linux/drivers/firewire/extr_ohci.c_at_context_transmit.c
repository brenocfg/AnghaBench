#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fw_packet {scalar_t__ generation; int /*<<< orphan*/  ack; int /*<<< orphan*/  (* callback ) (struct fw_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * header; } ;
struct context {TYPE_1__* ohci; } ;
struct TYPE_2__ {scalar_t__ node_id; scalar_t__ generation; int /*<<< orphan*/  card; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ HEADER_GET_DESTINATION (int /*<<< orphan*/ ) ; 
 int at_context_queue_packet (struct context*,struct fw_packet*) ; 
 int /*<<< orphan*/  handle_local_request (struct context*,struct fw_packet*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct fw_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at_context_transmit(struct context *ctx, struct fw_packet *packet)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctx->ohci->lock, flags);

	if (HEADER_GET_DESTINATION(packet->header[0]) == ctx->ohci->node_id &&
	    ctx->ohci->generation == packet->generation) {
		spin_unlock_irqrestore(&ctx->ohci->lock, flags);
		handle_local_request(ctx, packet);
		return;
	}

	ret = at_context_queue_packet(ctx, packet);
	spin_unlock_irqrestore(&ctx->ohci->lock, flags);

	if (ret < 0)
		packet->callback(packet, &ctx->ohci->card, packet->ack);

}