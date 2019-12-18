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
struct a10hdmiaudio_chinfo {int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_DMA_HALT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a10hdmiaudio_stop(struct a10hdmiaudio_chinfo *ch)
{
	/* Disable DMA channel */
	SUNXI_DMA_HALT(ch->dmac, ch->dmachan);
}