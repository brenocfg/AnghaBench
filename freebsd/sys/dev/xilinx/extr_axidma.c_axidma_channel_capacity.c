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
struct TYPE_3__ {scalar_t__ chan; } ;
typedef  TYPE_1__ xdma_channel_t ;
typedef  scalar_t__ uint32_t ;
struct axidma_channel {scalar_t__ descs_used_count; scalar_t__ descs_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

__attribute__((used)) static int
axidma_channel_capacity(device_t dev, xdma_channel_t *xchan,
    uint32_t *capacity)
{
	struct axidma_channel *chan;
	uint32_t c;

	chan = (struct axidma_channel *)xchan->chan;

	/* At least one descriptor must be left empty. */
	c = (chan->descs_num - chan->descs_used_count - 1);

	*capacity = c;

	return (0);
}