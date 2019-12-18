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
struct pl330_dmac {int quirks; } ;
struct _xfer_spec {TYPE_1__* desc; } ;
typedef  enum pl330_cond { ____Placeholder_pl330_cond } pl330_cond ;
struct TYPE_2__ {int /*<<< orphan*/  peri; int /*<<< orphan*/  rqtype; } ;

/* Variables and functions */
 int BURST ; 
 int PL330_QUIRK_BROKEN_NO_FLUSHP ; 
 scalar_t__ _emit_FLUSHP (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _emit_WFP (unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _emit_load (unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _emit_store (unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _ldst_peripheral(struct pl330_dmac *pl330,
				 unsigned dry_run, u8 buf[],
				 const struct _xfer_spec *pxs, int cyc,
				 enum pl330_cond cond)
{
	int off = 0;

	if (pl330->quirks & PL330_QUIRK_BROKEN_NO_FLUSHP)
		cond = BURST;

	/*
	 * do FLUSHP at beginning to clear any stale dma requests before the
	 * first WFP.
	 */
	if (!(pl330->quirks & PL330_QUIRK_BROKEN_NO_FLUSHP))
		off += _emit_FLUSHP(dry_run, &buf[off], pxs->desc->peri);
	while (cyc--) {
		off += _emit_WFP(dry_run, &buf[off], cond, pxs->desc->peri);
		off += _emit_load(dry_run, &buf[off], cond, pxs->desc->rqtype,
			pxs->desc->peri);
		off += _emit_store(dry_run, &buf[off], cond, pxs->desc->rqtype,
			pxs->desc->peri);
	}

	return off;
}