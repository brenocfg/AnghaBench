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
struct hci_uart {struct ath_struct* priv; } ;
struct ath_struct {int /*<<< orphan*/  ctxtsw; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ath_struct*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath_close(struct hci_uart *hu)
{
	struct ath_struct *ath = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ath->txq);

	kfree_skb(ath->rx_skb);

	cancel_work_sync(&ath->ctxtsw);

	hu->priv = NULL;
	kfree(ath);

	return 0;
}