#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_dmatag; } ;
typedef  TYPE_1__ dbdma_channel_t ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dbdma_sync_commands(dbdma_channel_t *chan, bus_dmasync_op_t op)
{

	bus_dmamap_sync(chan->sc_dmatag, chan->sc_dmamap, op);
}