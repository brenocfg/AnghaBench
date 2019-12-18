#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pl330_config {int /*<<< orphan*/  periph_id; } ;
struct _xfer_spec {TYPE_2__* desc; } ;
struct TYPE_3__ {struct pl330_config* pcfg; } ;
struct TYPE_4__ {TYPE_1__ rqcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS ; 
 scalar_t__ PERIPH_REV_R1P0 ; 
 scalar_t__ _emit_LD (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _emit_RMB (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ _emit_ST (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _emit_WMB (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_revision (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _ldst_memtomem(unsigned dry_run, u8 buf[],
		const struct _xfer_spec *pxs, int cyc)
{
	int off = 0;
	struct pl330_config *pcfg = pxs->desc->rqcfg.pcfg;

	/* check lock-up free version */
	if (get_revision(pcfg->periph_id) >= PERIPH_REV_R1P0) {
		while (cyc--) {
			off += _emit_LD(dry_run, &buf[off], ALWAYS);
			off += _emit_ST(dry_run, &buf[off], ALWAYS);
		}
	} else {
		while (cyc--) {
			off += _emit_LD(dry_run, &buf[off], ALWAYS);
			off += _emit_RMB(dry_run, &buf[off]);
			off += _emit_ST(dry_run, &buf[off], ALWAYS);
			off += _emit_WMB(dry_run, &buf[off]);
		}
	}

	return off;
}