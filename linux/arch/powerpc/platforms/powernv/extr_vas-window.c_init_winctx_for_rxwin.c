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
struct vas_window {int /*<<< orphan*/  wcreds_max; } ;
struct vas_winctx {int pin_win; int fault_win; int data_stamp; int intr_disable; int notify_after_count; int notify_disable; int fifo_disable; int /*<<< orphan*/  max_scope; int /*<<< orphan*/  min_scope; int /*<<< orphan*/  tc_mode; int /*<<< orphan*/  dma_type; int /*<<< orphan*/  pswid; int /*<<< orphan*/  lnotify_tid; int /*<<< orphan*/  lnotify_pid; int /*<<< orphan*/  lnotify_lpid; int /*<<< orphan*/ * rx_fifo; scalar_t__ user_win; int /*<<< orphan*/  tx_word_mode; int /*<<< orphan*/  rx_word_mode; scalar_t__ nx_win; int /*<<< orphan*/  notify_early; int /*<<< orphan*/  tx_wcred_mode; int /*<<< orphan*/  rx_wcred_mode; int /*<<< orphan*/  rej_no_credit; int /*<<< orphan*/  wcreds_max; int /*<<< orphan*/  rx_fifo_size; } ;
struct vas_rx_win_attr {int pin_win; int fault_win; int /*<<< orphan*/  tc_mode; int /*<<< orphan*/  pswid; int /*<<< orphan*/  lnotify_tid; int /*<<< orphan*/  lnotify_pid; int /*<<< orphan*/  lnotify_lpid; int /*<<< orphan*/  notify_early; int /*<<< orphan*/  tx_wcred_mode; int /*<<< orphan*/  rx_wcred_mode; int /*<<< orphan*/  tx_win_ord_mode; int /*<<< orphan*/  rx_win_ord_mode; int /*<<< orphan*/  rej_no_credit; scalar_t__ user_win; scalar_t__ nx_win; int /*<<< orphan*/  rx_fifo_size; int /*<<< orphan*/ * rx_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAS_DMA_TYPE_INJECT ; 
 int /*<<< orphan*/  VAS_SCOPE_LOCAL ; 
 int /*<<< orphan*/  VAS_SCOPE_VECTORED_GROUP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (struct vas_winctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_winctx_for_rxwin(struct vas_window *rxwin,
			struct vas_rx_win_attr *rxattr,
			struct vas_winctx *winctx)
{
	/*
	 * We first zero (memset()) all fields and only set non-zero fields.
	 * Following fields are 0/false but maybe deserve a comment:
	 *
	 *	->notify_os_intr_reg	In powerNV, send intrs to HV
	 *	->notify_disable	False for NX windows
	 *	->intr_disable		False for Fault Windows
	 *	->xtra_write		False for NX windows
	 *	->notify_early		NA for NX windows
	 *	->rsvd_txbuf_count	NA for Rx windows
	 *	->lpid, ->pid, ->tid	NA for Rx windows
	 */

	memset(winctx, 0, sizeof(struct vas_winctx));

	winctx->rx_fifo = rxattr->rx_fifo;
	winctx->rx_fifo_size = rxattr->rx_fifo_size;
	winctx->wcreds_max = rxwin->wcreds_max;
	winctx->pin_win = rxattr->pin_win;

	winctx->nx_win = rxattr->nx_win;
	winctx->fault_win = rxattr->fault_win;
	winctx->user_win = rxattr->user_win;
	winctx->rej_no_credit = rxattr->rej_no_credit;
	winctx->rx_word_mode = rxattr->rx_win_ord_mode;
	winctx->tx_word_mode = rxattr->tx_win_ord_mode;
	winctx->rx_wcred_mode = rxattr->rx_wcred_mode;
	winctx->tx_wcred_mode = rxattr->tx_wcred_mode;
	winctx->notify_early = rxattr->notify_early;

	if (winctx->nx_win) {
		winctx->data_stamp = true;
		winctx->intr_disable = true;
		winctx->pin_win = true;

		WARN_ON_ONCE(winctx->fault_win);
		WARN_ON_ONCE(!winctx->rx_word_mode);
		WARN_ON_ONCE(!winctx->tx_word_mode);
		WARN_ON_ONCE(winctx->notify_after_count);
	} else if (winctx->fault_win) {
		winctx->notify_disable = true;
	} else if (winctx->user_win) {
		/*
		 * Section 1.8.1 Low Latency Core-Core Wake up of
		 * the VAS workbook:
		 *
		 *      - disable credit checks ([tr]x_wcred_mode = false)
		 *      - disable FIFO writes
		 *      - enable ASB_Notify, disable interrupt
		 */
		winctx->fifo_disable = true;
		winctx->intr_disable = true;
		winctx->rx_fifo = NULL;
	}

	winctx->lnotify_lpid = rxattr->lnotify_lpid;
	winctx->lnotify_pid = rxattr->lnotify_pid;
	winctx->lnotify_tid = rxattr->lnotify_tid;
	winctx->pswid = rxattr->pswid;
	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = rxattr->tc_mode;

	winctx->min_scope = VAS_SCOPE_LOCAL;
	winctx->max_scope = VAS_SCOPE_VECTORED_GROUP;
}