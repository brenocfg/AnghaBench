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
typedef  unsigned long long u64 ;
struct vas_window {int dummy; } ;
struct vas_winctx {int lpid; int pidr; int irq_port; int pswid; int data_stamp; int dma_type; int fifo_disable; int wcreds_max; int rx_fifo_size; int rx_win_id; int notify_disable; int intr_disable; int notify_early; int notify_os_intr_reg; int lnotify_pid; int lnotify_lpid; int lnotify_tid; int min_scope; int max_scope; int rej_no_credit; int pin_win; int tx_wcred_mode; int rx_wcred_mode; int tx_word_mode; int rx_word_mode; int fault_win; int nx_win; int /*<<< orphan*/  rx_fifo; int /*<<< orphan*/  user_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_MSG_COUNT ; 
 int /*<<< orphan*/  FAULT_TX_WIN ; 
 int /*<<< orphan*/  HV_INTR_SRC_RA ; 
 int /*<<< orphan*/  LDATA_STAMP_CTL ; 
 int /*<<< orphan*/  LDMA_CACHE_CTL ; 
 int /*<<< orphan*/  LFIFO_BAR ; 
 int /*<<< orphan*/  LFIFO_SIZE ; 
 int /*<<< orphan*/  LNOTIFY_AFTER_COUNT ; 
 int /*<<< orphan*/  LNOTIFY_CTL ; 
 int /*<<< orphan*/  LNOTIFY_LPID ; 
 int /*<<< orphan*/  LNOTIFY_PID ; 
 int /*<<< orphan*/  LNOTIFY_SCOPE ; 
 int /*<<< orphan*/  LNOTIFY_TID ; 
 int /*<<< orphan*/  LPID ; 
 int /*<<< orphan*/  LRFIFO_PUSH ; 
 int /*<<< orphan*/  LRFIFO_WIN_PTR ; 
 int /*<<< orphan*/  LRX_WCRED ; 
 int /*<<< orphan*/  LRX_WCRED_ADDER ; 
 int /*<<< orphan*/  NX_UTIL_ADDER ; 
 int /*<<< orphan*/  OSU_INTR_SRC_RA ; 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  PSWID ; 
 unsigned long long SET_FIELD (int /*<<< orphan*/ ,unsigned long long,int) ; 
 int /*<<< orphan*/  SPARE1 ; 
 int /*<<< orphan*/  SPARE2 ; 
 int /*<<< orphan*/  SPARE3 ; 
 int /*<<< orphan*/  SPARE4 ; 
 int /*<<< orphan*/  SPARE5 ; 
 int /*<<< orphan*/  SPARE6 ; 
 int /*<<< orphan*/  TX_WCRED ; 
 int /*<<< orphan*/  TX_WCRED_ADDER ; 
 int /*<<< orphan*/  VAS_FAULT_TX_WIN ; 
 int /*<<< orphan*/  VAS_HV_INTR_SRC_RA ; 
 int /*<<< orphan*/  VAS_INTR_DISABLE ; 
 int /*<<< orphan*/  VAS_LDATA_STAMP ; 
 int /*<<< orphan*/  VAS_LDMA_FIFO_DISABLE ; 
 int /*<<< orphan*/  VAS_LDMA_TYPE ; 
 int /*<<< orphan*/  VAS_LFIFO_SIZE ; 
 int /*<<< orphan*/  VAS_LNOTIFY_LPID ; 
 int /*<<< orphan*/  VAS_LNOTIFY_MAX_SCOPE ; 
 int /*<<< orphan*/  VAS_LNOTIFY_MIN_SCOPE ; 
 int /*<<< orphan*/  VAS_LNOTIFY_PID ; 
 int /*<<< orphan*/  VAS_LNOTIFY_TID ; 
 int /*<<< orphan*/  VAS_LPID ; 
 int /*<<< orphan*/  VAS_LRX_WCRED ; 
 int /*<<< orphan*/  VAS_LRX_WIN_ID ; 
 int /*<<< orphan*/  VAS_NOTIFY_DISABLE ; 
 int /*<<< orphan*/  VAS_NOTIFY_EARLY ; 
 int /*<<< orphan*/  VAS_NOTIFY_OSU_INTR ; 
 int /*<<< orphan*/  VAS_PAGE_MIGRATION_SELECT ; 
 int /*<<< orphan*/  VAS_PID_ID ; 
 int /*<<< orphan*/  VAS_PSWID_EA_HANDLE ; 
 int /*<<< orphan*/  VAS_PUSH_TO_MEM ; 
 int /*<<< orphan*/  VAS_TX_WCRED ; 
 int /*<<< orphan*/  VAS_WINCTL_FAULT_WIN ; 
 int /*<<< orphan*/  VAS_WINCTL_NX_WIN ; 
 int /*<<< orphan*/  VAS_WINCTL_OPEN ; 
 int /*<<< orphan*/  VAS_WINCTL_PIN ; 
 int /*<<< orphan*/  VAS_WINCTL_REJ_NO_CREDIT ; 
 int /*<<< orphan*/  VAS_WINCTL_RX_WCRED_MODE ; 
 int /*<<< orphan*/  VAS_WINCTL_RX_WORD_MODE ; 
 int /*<<< orphan*/  VAS_WINCTL_TX_WCRED_MODE ; 
 int /*<<< orphan*/  VAS_WINCTL_TX_WORD_MODE ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINCTL ; 
 int /*<<< orphan*/  WIN_CTX_CACHING_CTL ; 
 int /*<<< orphan*/  WIN_STATUS ; 
 unsigned long long __pa (int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  init_rsvd_tx_buf_count (struct vas_window*,struct vas_winctx*) ; 
 int /*<<< orphan*/  init_xlate_regs (struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_window_regs (struct vas_window*) ; 
 int /*<<< orphan*/  write_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ,unsigned long long) ; 

int init_winctx_regs(struct vas_window *window, struct vas_winctx *winctx)
{
	u64 val;
	int fifo_size;

	reset_window_regs(window);

	val = 0ULL;
	val = SET_FIELD(VAS_LPID, val, winctx->lpid);
	write_hvwc_reg(window, VREG(LPID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_PID_ID, val, winctx->pidr);
	write_hvwc_reg(window, VREG(PID), val);

	init_xlate_regs(window, winctx->user_win);

	val = 0ULL;
	val = SET_FIELD(VAS_FAULT_TX_WIN, val, 0);
	write_hvwc_reg(window, VREG(FAULT_TX_WIN), val);

	/* In PowerNV, interrupts go to HV. */
	write_hvwc_reg(window, VREG(OSU_INTR_SRC_RA), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_HV_INTR_SRC_RA, val, winctx->irq_port);
	write_hvwc_reg(window, VREG(HV_INTR_SRC_RA), val);

	val = 0ULL;
	val = SET_FIELD(VAS_PSWID_EA_HANDLE, val, winctx->pswid);
	write_hvwc_reg(window, VREG(PSWID), val);

	write_hvwc_reg(window, VREG(SPARE1), 0ULL);
	write_hvwc_reg(window, VREG(SPARE2), 0ULL);
	write_hvwc_reg(window, VREG(SPARE3), 0ULL);

	/*
	 * NOTE: VAS expects the FIFO address to be copied into the LFIFO_BAR
	 *	 register as is - do NOT shift the address into VAS_LFIFO_BAR
	 *	 bit fields! Ok to set the page migration select fields -
	 *	 VAS ignores the lower 10+ bits in the address anyway, because
	 *	 the minimum FIFO size is 1K?
	 *
	 * See also: Design note in function header.
	 */
	val = __pa(winctx->rx_fifo);
	val = SET_FIELD(VAS_PAGE_MIGRATION_SELECT, val, 0);
	write_hvwc_reg(window, VREG(LFIFO_BAR), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LDATA_STAMP, val, winctx->data_stamp);
	write_hvwc_reg(window, VREG(LDATA_STAMP_CTL), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LDMA_TYPE, val, winctx->dma_type);
	val = SET_FIELD(VAS_LDMA_FIFO_DISABLE, val, winctx->fifo_disable);
	write_hvwc_reg(window, VREG(LDMA_CACHE_CTL), val);

	write_hvwc_reg(window, VREG(LRFIFO_PUSH), 0ULL);
	write_hvwc_reg(window, VREG(CURR_MSG_COUNT), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_AFTER_COUNT), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_LRX_WCRED, val, winctx->wcreds_max);
	write_hvwc_reg(window, VREG(LRX_WCRED), val);

	val = 0ULL;
	val = SET_FIELD(VAS_TX_WCRED, val, winctx->wcreds_max);
	write_hvwc_reg(window, VREG(TX_WCRED), val);

	write_hvwc_reg(window, VREG(LRX_WCRED_ADDER), 0ULL);
	write_hvwc_reg(window, VREG(TX_WCRED_ADDER), 0ULL);

	fifo_size = winctx->rx_fifo_size / 1024;

	val = 0ULL;
	val = SET_FIELD(VAS_LFIFO_SIZE, val, ilog2(fifo_size));
	write_hvwc_reg(window, VREG(LFIFO_SIZE), val);

	/* Update window control and caching control registers last so
	 * we mark the window open only after fully initializing it and
	 * pushing context to cache.
	 */

	write_hvwc_reg(window, VREG(WIN_STATUS), 0ULL);

	init_rsvd_tx_buf_count(window, winctx);

	/* for a send window, point to the matching receive window */
	val = 0ULL;
	val = SET_FIELD(VAS_LRX_WIN_ID, val, winctx->rx_win_id);
	write_hvwc_reg(window, VREG(LRFIFO_WIN_PTR), val);

	write_hvwc_reg(window, VREG(SPARE4), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_NOTIFY_DISABLE, val, winctx->notify_disable);
	val = SET_FIELD(VAS_INTR_DISABLE, val, winctx->intr_disable);
	val = SET_FIELD(VAS_NOTIFY_EARLY, val, winctx->notify_early);
	val = SET_FIELD(VAS_NOTIFY_OSU_INTR, val, winctx->notify_os_intr_reg);
	write_hvwc_reg(window, VREG(LNOTIFY_CTL), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_PID, val, winctx->lnotify_pid);
	write_hvwc_reg(window, VREG(LNOTIFY_PID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_LPID, val, winctx->lnotify_lpid);
	write_hvwc_reg(window, VREG(LNOTIFY_LPID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_TID, val, winctx->lnotify_tid);
	write_hvwc_reg(window, VREG(LNOTIFY_TID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_MIN_SCOPE, val, winctx->min_scope);
	val = SET_FIELD(VAS_LNOTIFY_MAX_SCOPE, val, winctx->max_scope);
	write_hvwc_reg(window, VREG(LNOTIFY_SCOPE), val);

	/* Skip read-only registers NX_UTIL and NX_UTIL_SE */

	write_hvwc_reg(window, VREG(SPARE5), 0ULL);
	write_hvwc_reg(window, VREG(NX_UTIL_ADDER), 0ULL);
	write_hvwc_reg(window, VREG(SPARE6), 0ULL);

	/* Finally, push window context to memory and... */
	val = 0ULL;
	val = SET_FIELD(VAS_PUSH_TO_MEM, val, 1);
	write_hvwc_reg(window, VREG(WIN_CTX_CACHING_CTL), val);

	/* ... mark the window open for business */
	val = 0ULL;
	val = SET_FIELD(VAS_WINCTL_REJ_NO_CREDIT, val, winctx->rej_no_credit);
	val = SET_FIELD(VAS_WINCTL_PIN, val, winctx->pin_win);
	val = SET_FIELD(VAS_WINCTL_TX_WCRED_MODE, val, winctx->tx_wcred_mode);
	val = SET_FIELD(VAS_WINCTL_RX_WCRED_MODE, val, winctx->rx_wcred_mode);
	val = SET_FIELD(VAS_WINCTL_TX_WORD_MODE, val, winctx->tx_word_mode);
	val = SET_FIELD(VAS_WINCTL_RX_WORD_MODE, val, winctx->rx_word_mode);
	val = SET_FIELD(VAS_WINCTL_FAULT_WIN, val, winctx->fault_win);
	val = SET_FIELD(VAS_WINCTL_NX_WIN, val, winctx->nx_win);
	val = SET_FIELD(VAS_WINCTL_OPEN, val, 1);
	write_hvwc_reg(window, VREG(WINCTL), val);

	return 0;
}