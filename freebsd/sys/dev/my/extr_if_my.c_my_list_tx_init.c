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
struct my_chain_data {int /*<<< orphan*/ * my_tx_head; int /*<<< orphan*/  my_tx_tail; TYPE_1__* my_tx_chain; TYPE_1__* my_tx_free; } ;
struct my_softc {struct my_list_data* my_ldata; struct my_chain_data my_cdata; } ;
struct my_list_data {int /*<<< orphan*/ * my_tx_list; } ;
struct TYPE_2__ {struct TYPE_2__* my_nextdesc; int /*<<< orphan*/ * my_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_TX_LIST_CNT ; 

__attribute__((used)) static int
my_list_tx_init(struct my_softc * sc)
{
	struct my_chain_data *cd;
	struct my_list_data *ld;
	int             i;

	MY_LOCK_ASSERT(sc);
	cd = &sc->my_cdata;
	ld = sc->my_ldata;
	for (i = 0; i < MY_TX_LIST_CNT; i++) {
		cd->my_tx_chain[i].my_ptr = &ld->my_tx_list[i];
		if (i == (MY_TX_LIST_CNT - 1))
			cd->my_tx_chain[i].my_nextdesc = &cd->my_tx_chain[0];
		else
			cd->my_tx_chain[i].my_nextdesc =
			    &cd->my_tx_chain[i + 1];
	}
	cd->my_tx_free = &cd->my_tx_chain[0];
	cd->my_tx_tail = cd->my_tx_head = NULL;
	return (0);
}