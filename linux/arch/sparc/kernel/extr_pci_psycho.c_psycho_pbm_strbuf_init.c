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
struct TYPE_2__ {unsigned long volatile* strbuf_flushflag; unsigned long strbuf_flushflag_pa; int strbuf_enabled; scalar_t__ strbuf_control; int /*<<< orphan*/ * __flushflag_buf; scalar_t__ strbuf_ctxmatch_base; scalar_t__ strbuf_ctxflush; scalar_t__ strbuf_line_diag; scalar_t__ strbuf_tag_diag; scalar_t__ strbuf_err_stat; scalar_t__ strbuf_fsync; scalar_t__ strbuf_pflush; } ;
struct pci_pbm_info {unsigned long controller_regs; TYPE_1__ stc; } ;

/* Variables and functions */
 scalar_t__ PSYCHO_STC_ERR_A ; 
 scalar_t__ PSYCHO_STC_ERR_B ; 
 scalar_t__ PSYCHO_STC_LINE_A ; 
 scalar_t__ PSYCHO_STC_LINE_B ; 
 scalar_t__ PSYCHO_STC_TAG_A ; 
 scalar_t__ PSYCHO_STC_TAG_B ; 
 scalar_t__ PSYCHO_STRBUF_CONTROL_A ; 
 scalar_t__ PSYCHO_STRBUF_CONTROL_B ; 
 int PSYCHO_STRBUF_CTRL_ENAB ; 
 int PSYCHO_STRBUF_CTRL_LENAB ; 
 int PSYCHO_STRBUF_CTRL_LPTR ; 
 int PSYCHO_STRBUF_CTRL_RRDIS ; 
 scalar_t__ PSYCHO_STRBUF_FLUSH_A ; 
 scalar_t__ PSYCHO_STRBUF_FLUSH_B ; 
 scalar_t__ PSYCHO_STRBUF_FSYNC_A ; 
 scalar_t__ PSYCHO_STRBUF_FSYNC_B ; 
 scalar_t__ __pa (unsigned long volatile*) ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void psycho_pbm_strbuf_init(struct pci_pbm_info *pbm,
				   int is_pbm_a)
{
	unsigned long base = pbm->controller_regs;
	u64 control;

	if (is_pbm_a) {
		pbm->stc.strbuf_control  = base + PSYCHO_STRBUF_CONTROL_A;
		pbm->stc.strbuf_pflush   = base + PSYCHO_STRBUF_FLUSH_A;
		pbm->stc.strbuf_fsync    = base + PSYCHO_STRBUF_FSYNC_A;
		pbm->stc.strbuf_err_stat = base + PSYCHO_STC_ERR_A;
		pbm->stc.strbuf_tag_diag = base + PSYCHO_STC_TAG_A;
		pbm->stc.strbuf_line_diag= base + PSYCHO_STC_LINE_A;
	} else {
		pbm->stc.strbuf_control  = base + PSYCHO_STRBUF_CONTROL_B;
		pbm->stc.strbuf_pflush   = base + PSYCHO_STRBUF_FLUSH_B;
		pbm->stc.strbuf_fsync    = base + PSYCHO_STRBUF_FSYNC_B;
		pbm->stc.strbuf_err_stat = base + PSYCHO_STC_ERR_B;
		pbm->stc.strbuf_tag_diag = base + PSYCHO_STC_TAG_B;
		pbm->stc.strbuf_line_diag= base + PSYCHO_STC_LINE_B;
	}
	/* PSYCHO's streaming buffer lacks ctx flushing. */
	pbm->stc.strbuf_ctxflush      = 0;
	pbm->stc.strbuf_ctxmatch_base = 0;

	pbm->stc.strbuf_flushflag = (volatile unsigned long *)
		((((unsigned long)&pbm->stc.__flushflag_buf[0])
		  + 63UL)
		 & ~63UL);
	pbm->stc.strbuf_flushflag_pa = (unsigned long)
		__pa(pbm->stc.strbuf_flushflag);

	/* Enable the streaming buffer.  We have to be careful
	 * just in case OBP left it with LRU locking enabled.
	 *
	 * It is possible to control if PBM will be rerun on
	 * line misses.  Currently I just retain whatever setting
	 * OBP left us with.  All checks so far show it having
	 * a value of zero.
	 */
#undef PSYCHO_STRBUF_RERUN_ENABLE
#undef PSYCHO_STRBUF_RERUN_DISABLE
	control = upa_readq(pbm->stc.strbuf_control);
	control |= PSYCHO_STRBUF_CTRL_ENAB;
	control &= ~(PSYCHO_STRBUF_CTRL_LENAB | PSYCHO_STRBUF_CTRL_LPTR);
#ifdef PSYCHO_STRBUF_RERUN_ENABLE
	control &= ~(PSYCHO_STRBUF_CTRL_RRDIS);
#else
#ifdef PSYCHO_STRBUF_RERUN_DISABLE
	control |= PSYCHO_STRBUF_CTRL_RRDIS;
#endif
#endif
	upa_writeq(control, pbm->stc.strbuf_control);

	pbm->stc.strbuf_enabled = 1;
}