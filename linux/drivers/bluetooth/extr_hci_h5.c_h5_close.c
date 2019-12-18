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
struct hci_uart {int /*<<< orphan*/  serdev; struct h5* priv; } ;
struct h5 {TYPE_1__* vnd; int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; int /*<<< orphan*/  unack; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct h5*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct h5*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct h5*) ; 

__attribute__((used)) static int h5_close(struct hci_uart *hu)
{
	struct h5 *h5 = hu->priv;

	del_timer_sync(&h5->timer);

	skb_queue_purge(&h5->unack);
	skb_queue_purge(&h5->rel);
	skb_queue_purge(&h5->unrel);

	if (h5->vnd && h5->vnd->close)
		h5->vnd->close(h5);

	if (!hu->serdev)
		kfree(h5);

	return 0;
}