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
struct vas_window {TYPE_1__* rxwin; int /*<<< orphan*/  wcreds_max; } ;
struct vas_winctx {int intr_disable; int data_stamp; scalar_t__ pswid; int /*<<< orphan*/  max_scope; int /*<<< orphan*/  min_scope; int /*<<< orphan*/  tc_mode; int /*<<< orphan*/  dma_type; int /*<<< orphan*/  rx_win_id; int /*<<< orphan*/  pidr; int /*<<< orphan*/  lpid; scalar_t__ nx_win; int /*<<< orphan*/  rsvd_txbuf_count; int /*<<< orphan*/  tx_word_mode; int /*<<< orphan*/  rx_word_mode; int /*<<< orphan*/  tx_wcred_mode; int /*<<< orphan*/  rx_wcred_mode; int /*<<< orphan*/  rsvd_txbuf_enable; int /*<<< orphan*/  rej_no_credit; int /*<<< orphan*/  pin_win; int /*<<< orphan*/  user_win; int /*<<< orphan*/  wcreds_max; } ;
struct vas_tx_win_attr {int /*<<< orphan*/  tc_mode; int /*<<< orphan*/  pidr; int /*<<< orphan*/  lpid; int /*<<< orphan*/  rsvd_txbuf_count; int /*<<< orphan*/  tx_win_ord_mode; int /*<<< orphan*/  rx_win_ord_mode; int /*<<< orphan*/  tx_wcred_mode; int /*<<< orphan*/  rx_wcred_mode; int /*<<< orphan*/  rsvd_txbuf_enable; int /*<<< orphan*/  rej_no_credit; int /*<<< orphan*/  pin_win; int /*<<< orphan*/  user_win; } ;
struct TYPE_2__ {int /*<<< orphan*/  winid; scalar_t__ nx_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAS_DMA_TYPE_INJECT ; 
 int /*<<< orphan*/  VAS_SCOPE_LOCAL ; 
 int /*<<< orphan*/  VAS_SCOPE_VECTORED_GROUP ; 
 int /*<<< orphan*/  memset (struct vas_winctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_winctx_for_txwin(struct vas_window *txwin,
			struct vas_tx_win_attr *txattr,
			struct vas_winctx *winctx)
{
	/*
	 * We first zero all fields and only set non-zero ones. Following
	 * are some fields set to 0/false for the stated reason:
	 *
	 *	->notify_os_intr_reg	In powernv, send intrs to HV
	 *	->rsvd_txbuf_count	Not supported yet.
	 *	->notify_disable	False for NX windows
	 *	->xtra_write		False for NX windows
	 *	->notify_early		NA for NX windows
	 *	->lnotify_lpid		NA for Tx windows
	 *	->lnotify_pid		NA for Tx windows
	 *	->lnotify_tid		NA for Tx windows
	 *	->tx_win_cred_mode	Ignore for now for NX windows
	 *	->rx_win_cred_mode	Ignore for now for NX windows
	 */
	memset(winctx, 0, sizeof(struct vas_winctx));

	winctx->wcreds_max = txwin->wcreds_max;

	winctx->user_win = txattr->user_win;
	winctx->nx_win = txwin->rxwin->nx_win;
	winctx->pin_win = txattr->pin_win;
	winctx->rej_no_credit = txattr->rej_no_credit;
	winctx->rsvd_txbuf_enable = txattr->rsvd_txbuf_enable;

	winctx->rx_wcred_mode = txattr->rx_wcred_mode;
	winctx->tx_wcred_mode = txattr->tx_wcred_mode;
	winctx->rx_word_mode = txattr->rx_win_ord_mode;
	winctx->tx_word_mode = txattr->tx_win_ord_mode;
	winctx->rsvd_txbuf_count = txattr->rsvd_txbuf_count;

	winctx->intr_disable = true;
	if (winctx->nx_win)
		winctx->data_stamp = true;

	winctx->lpid = txattr->lpid;
	winctx->pidr = txattr->pidr;
	winctx->rx_win_id = txwin->rxwin->winid;

	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = txattr->tc_mode;
	winctx->min_scope = VAS_SCOPE_LOCAL;
	winctx->max_scope = VAS_SCOPE_VECTORED_GROUP;

	winctx->pswid = 0;
}