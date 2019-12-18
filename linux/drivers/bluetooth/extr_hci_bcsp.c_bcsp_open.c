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
struct hci_uart {struct bcsp_struct* priv; } ;
struct bcsp_struct {int use_crc; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  tbcsp; int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; int /*<<< orphan*/  unack; struct hci_uart* hu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCSP_W4_PKT_DELIMITER ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcsp_timed_event ; 
 struct bcsp_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ txcrc ; 

__attribute__((used)) static int bcsp_open(struct hci_uart *hu)
{
	struct bcsp_struct *bcsp;

	BT_DBG("hu %p", hu);

	bcsp = kzalloc(sizeof(*bcsp), GFP_KERNEL);
	if (!bcsp)
		return -ENOMEM;

	hu->priv = bcsp;
	bcsp->hu = hu;
	skb_queue_head_init(&bcsp->unack);
	skb_queue_head_init(&bcsp->rel);
	skb_queue_head_init(&bcsp->unrel);

	timer_setup(&bcsp->tbcsp, bcsp_timed_event, 0);

	bcsp->rx_state = BCSP_W4_PKT_DELIMITER;

	if (txcrc)
		bcsp->use_crc = 1;

	return 0;
}