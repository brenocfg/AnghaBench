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
struct hci_uart {int /*<<< orphan*/  hdev; struct ath_struct* priv; } ;
struct ath_struct {int /*<<< orphan*/ * rx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_recv_pkts ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * h4_recv_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath_recv(struct hci_uart *hu, const void *data, int count)
{
	struct ath_struct *ath = hu->priv;

	ath->rx_skb = h4_recv_buf(hu->hdev, ath->rx_skb, data, count,
				  ath_recv_pkts, ARRAY_SIZE(ath_recv_pkts));
	if (IS_ERR(ath->rx_skb)) {
		int err = PTR_ERR(ath->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		ath->rx_skb = NULL;
		return err;
	}

	return count;
}