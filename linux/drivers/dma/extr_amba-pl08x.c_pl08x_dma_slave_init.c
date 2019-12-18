#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct pl08x_dma_chan {int slave; TYPE_2__* cd; TYPE_1__ cfg; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus_id; } ;

/* Variables and functions */

__attribute__((used)) static void pl08x_dma_slave_init(struct pl08x_dma_chan *chan)
{
	chan->slave = true;
	chan->name = chan->cd->bus_id;
	chan->cfg.src_addr = chan->cd->addr;
	chan->cfg.dst_addr = chan->cd->addr;
}