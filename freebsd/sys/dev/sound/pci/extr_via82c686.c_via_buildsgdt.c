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
typedef  int u_int32_t ;
struct via_chinfo {int blksz; TYPE_1__* sgd_table; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int ptr; int flags; } ;

/* Variables and functions */
 int VIA_DMAOP_EOL ; 
 int VIA_DMAOP_FLAG ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_buildsgdt(struct via_chinfo *ch)
{
	u_int32_t phys_addr, flag;
	int i, segs, seg_size;

	/*
	 *  Build the scatter/gather DMA (SGD) table.
	 *  There are four slots in the table: two for play, two for record.
	 *  This creates two half-buffers, one of which is playing; the other
	 *  is feeding.
	 */
	seg_size = ch->blksz;
	segs = sndbuf_getsize(ch->buffer) / seg_size;
	phys_addr = sndbuf_getbufaddr(ch->buffer);

	for (i = 0; i < segs; i++) {
		flag = (i == segs - 1)? VIA_DMAOP_EOL : VIA_DMAOP_FLAG;
		ch->sgd_table[i].ptr = phys_addr + (i * seg_size);
		ch->sgd_table[i].flags = flag | seg_size;
	}

	return 0;
}