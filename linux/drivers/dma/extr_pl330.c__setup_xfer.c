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
struct pl330_xfer {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct pl330_dmac {int dummy; } ;
struct _xfer_spec {TYPE_1__* desc; } ;
struct TYPE_2__ {struct pl330_xfer px; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAR ; 
 int /*<<< orphan*/  SAR ; 
 scalar_t__ _emit_MOV (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _setup_loops (struct pl330_dmac*,unsigned int,int /*<<< orphan*/ *,struct _xfer_spec const*) ; 

__attribute__((used)) static inline int _setup_xfer(struct pl330_dmac *pl330,
			      unsigned dry_run, u8 buf[],
			      const struct _xfer_spec *pxs)
{
	struct pl330_xfer *x = &pxs->desc->px;
	int off = 0;

	/* DMAMOV SAR, x->src_addr */
	off += _emit_MOV(dry_run, &buf[off], SAR, x->src_addr);
	/* DMAMOV DAR, x->dst_addr */
	off += _emit_MOV(dry_run, &buf[off], DAR, x->dst_addr);

	/* Setup Loop(s) */
	off += _setup_loops(pl330, dry_run, &buf[off], pxs);

	return off;
}