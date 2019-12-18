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
struct a10codec_chinfo {scalar_t__ dir; TYPE_1__* parent; scalar_t__ run; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  dmac; scalar_t__ pos; scalar_t__ physaddr; scalar_t__ fifo; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int SUNXI_DMA_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
a10codec_transfer(struct a10codec_chinfo *ch)
{
	bus_addr_t src, dst;
	int error;

	if (ch->dir == PCMDIR_PLAY) {
		src = ch->physaddr + ch->pos;
		dst = ch->fifo;
	} else {
		src = ch->fifo;
		dst = ch->physaddr + ch->pos;
	}

	error = SUNXI_DMA_TRANSFER(ch->dmac, ch->dmachan, src, dst,
	    ch->blocksize);
	if (error) {
		ch->run = 0;
		device_printf(ch->parent->dev, "DMA transfer failed: %d\n",
		    error);
	}
}