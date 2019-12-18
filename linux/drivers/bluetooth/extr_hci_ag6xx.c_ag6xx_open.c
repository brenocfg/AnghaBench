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
struct hci_uart {struct ag6xx_data* priv; } ;
struct ag6xx_data {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ag6xx_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ag6xx_open(struct hci_uart *hu)
{
	struct ag6xx_data *ag6xx;

	BT_DBG("hu %p", hu);

	ag6xx = kzalloc(sizeof(*ag6xx), GFP_KERNEL);
	if (!ag6xx)
		return -ENOMEM;

	skb_queue_head_init(&ag6xx->txq);

	hu->priv = ag6xx;
	return 0;
}