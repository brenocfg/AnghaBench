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
struct rsxx_dma {int dummy; } ;
struct dma_tracker_list {TYPE_1__* list; } ;
struct TYPE_2__ {struct rsxx_dma* dma; } ;

/* Variables and functions */

__attribute__((used)) static void set_tracker_dma(struct dma_tracker_list *trackers,
			    int tag,
			    struct rsxx_dma *dma)
{
	trackers->list[tag].dma = dma;
}