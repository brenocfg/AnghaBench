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
struct netmap_kring {int tx; int /*<<< orphan*/  si; struct netmap_adapter* notify_na; } ;
struct netmap_adapter {scalar_t__* si_users; int /*<<< orphan*/ * si; } ;
typedef  enum txrx { ____Placeholder_txrx } txrx ;

/* Variables and functions */
 int NM_IRQ_COMPLETED ; 
 int /*<<< orphan*/  nm_os_selwakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
netmap_notify(struct netmap_kring *kring, int flags)
{
	struct netmap_adapter *na = kring->notify_na;
	enum txrx t = kring->tx;

	nm_os_selwakeup(&kring->si);
	/* optimization: avoid a wake up on the global
	 * queue if nobody has registered for more
	 * than one ring
	 */
	if (na->si_users[t] > 0)
		nm_os_selwakeup(&na->si[t]);

	return NM_IRQ_COMPLETED;
}