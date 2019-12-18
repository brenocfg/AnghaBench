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
typedef  int u64 ;
struct TYPE_2__ {unsigned long volatile* strbuf_flushflag; unsigned long strbuf_flushflag_pa; int strbuf_enabled; scalar_t__ strbuf_control; int /*<<< orphan*/ * __flushflag_buf; scalar_t__ strbuf_ctxmatch_base; scalar_t__ strbuf_ctxflush; scalar_t__ strbuf_fsync; scalar_t__ strbuf_pflush; } ;
struct pci_pbm_info {unsigned long pbm_regs; scalar_t__ chip_type; TYPE_1__ stc; } ;

/* Variables and functions */
 scalar_t__ PBM_CHIP_TYPE_TOMATILLO ; 
 scalar_t__ SCHIZO_STRBUF_CONTROL ; 
 int SCHIZO_STRBUF_CTRL_DENAB ; 
 int SCHIZO_STRBUF_CTRL_ENAB ; 
 int SCHIZO_STRBUF_CTRL_LENAB ; 
 int SCHIZO_STRBUF_CTRL_LPTR ; 
 scalar_t__ SCHIZO_STRBUF_CTXFLUSH ; 
 scalar_t__ SCHIZO_STRBUF_CTXMATCH ; 
 scalar_t__ SCHIZO_STRBUF_FLUSH ; 
 scalar_t__ SCHIZO_STRBUF_FSYNC ; 
 scalar_t__ __pa (unsigned long volatile*) ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void schizo_pbm_strbuf_init(struct pci_pbm_info *pbm)
{
	unsigned long base = pbm->pbm_regs;
	u64 control;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO) {
		/* TOMATILLO lacks streaming cache.  */
		return;
	}

	/* SCHIZO has context flushing. */
	pbm->stc.strbuf_control		= base + SCHIZO_STRBUF_CONTROL;
	pbm->stc.strbuf_pflush		= base + SCHIZO_STRBUF_FLUSH;
	pbm->stc.strbuf_fsync		= base + SCHIZO_STRBUF_FSYNC;
	pbm->stc.strbuf_ctxflush	= base + SCHIZO_STRBUF_CTXFLUSH;
	pbm->stc.strbuf_ctxmatch_base	= base + SCHIZO_STRBUF_CTXMATCH;

	pbm->stc.strbuf_flushflag = (volatile unsigned long *)
		((((unsigned long)&pbm->stc.__flushflag_buf[0])
		  + 63UL)
		 & ~63UL);
	pbm->stc.strbuf_flushflag_pa = (unsigned long)
		__pa(pbm->stc.strbuf_flushflag);

	/* Turn off LRU locking and diag mode, enable the
	 * streaming buffer and leave the rerun-disable
	 * setting however OBP set it.
	 */
	control = upa_readq(pbm->stc.strbuf_control);
	control &= ~(SCHIZO_STRBUF_CTRL_LPTR |
		     SCHIZO_STRBUF_CTRL_LENAB |
		     SCHIZO_STRBUF_CTRL_DENAB);
	control |= SCHIZO_STRBUF_CTRL_ENAB;
	upa_writeq(control, pbm->stc.strbuf_control);

	pbm->stc.strbuf_enabled = 1;
}