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
typedef  int /*<<< orphan*/  u8 ;
struct pl330_dmac {int dummy; } ;
struct _xfer_spec {int ccr; TYPE_1__* desc; } ;
struct TYPE_2__ {int rqtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int CC_DSTBRSTLEN_SHFT ; 
 int CC_SRCBRSTLEN_SHFT ; 
#define  DMA_DEV_TO_MEM 130 
#define  DMA_MEM_TO_DEV 129 
#define  DMA_MEM_TO_MEM 128 
 int /*<<< orphan*/  SINGLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _emit_MOV (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int _ldst_memtomem (unsigned int,int /*<<< orphan*/ *,struct _xfer_spec const*,int) ; 
 int _ldst_peripheral (struct pl330_dmac*,unsigned int,int /*<<< orphan*/ *,struct _xfer_spec const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _dregs(struct pl330_dmac *pl330, unsigned int dry_run, u8 buf[],
		const struct _xfer_spec *pxs, int transfer_length)
{
	int off = 0;
	int dregs_ccr;

	if (transfer_length == 0)
		return off;

	switch (pxs->desc->rqtype) {
	case DMA_MEM_TO_DEV:
		/* fall through */
	case DMA_DEV_TO_MEM:
		off += _ldst_peripheral(pl330, dry_run, &buf[off], pxs,
			transfer_length, SINGLE);
		break;

	case DMA_MEM_TO_MEM:
		dregs_ccr = pxs->ccr;
		dregs_ccr &= ~((0xf << CC_SRCBRSTLEN_SHFT) |
			(0xf << CC_DSTBRSTLEN_SHFT));
		dregs_ccr |= (((transfer_length - 1) & 0xf) <<
			CC_SRCBRSTLEN_SHFT);
		dregs_ccr |= (((transfer_length - 1) & 0xf) <<
			CC_DSTBRSTLEN_SHFT);
		off += _emit_MOV(dry_run, &buf[off], CCR, dregs_ccr);
		off += _ldst_memtomem(dry_run, &buf[off], pxs, 1);
		break;

	default:
		/* this code should be unreachable */
		WARN_ON(1);
		break;
	}

	return off;
}