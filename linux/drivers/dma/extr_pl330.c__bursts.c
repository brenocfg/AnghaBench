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
struct _xfer_spec {TYPE_1__* desc; int /*<<< orphan*/  ccr; } ;
typedef  enum pl330_cond { ____Placeholder_pl330_cond } pl330_cond ;
struct TYPE_2__ {int rqtype; } ;

/* Variables and functions */
 int BRST_LEN (int /*<<< orphan*/ ) ; 
 int BURST ; 
#define  DMA_DEV_TO_MEM 130 
#define  DMA_MEM_TO_DEV 129 
#define  DMA_MEM_TO_MEM 128 
 int SINGLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _ldst_memtomem (unsigned int,int /*<<< orphan*/ *,struct _xfer_spec const*,int) ; 
 int _ldst_peripheral (struct pl330_dmac*,unsigned int,int /*<<< orphan*/ *,struct _xfer_spec const*,int,int) ; 

__attribute__((used)) static int _bursts(struct pl330_dmac *pl330, unsigned dry_run, u8 buf[],
		const struct _xfer_spec *pxs, int cyc)
{
	int off = 0;
	enum pl330_cond cond = BRST_LEN(pxs->ccr) > 1 ? BURST : SINGLE;

	switch (pxs->desc->rqtype) {
	case DMA_MEM_TO_DEV:
		/* fall through */
	case DMA_DEV_TO_MEM:
		off += _ldst_peripheral(pl330, dry_run, &buf[off], pxs, cyc,
			cond);
		break;

	case DMA_MEM_TO_MEM:
		off += _ldst_memtomem(dry_run, &buf[off], pxs, cyc);
		break;

	default:
		/* this code should be unreachable */
		WARN_ON(1);
		break;
	}

	return off;
}