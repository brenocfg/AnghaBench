#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct my_chain_data {TYPE_2__* my_rx_chain; TYPE_2__* my_rx_head; } ;
struct my_softc {struct my_list_data* my_ldata; struct my_chain_data my_cdata; } ;
struct my_list_data {TYPE_1__* my_rx_list; } ;
struct my_desc {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* my_nextdesc; struct my_desc* my_ptr; } ;
struct TYPE_3__ {void* my_next; } ;

/* Variables and functions */
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_RX_LIST_CNT ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 scalar_t__ my_newbuf (struct my_softc*,TYPE_2__*) ; 
 void* vtophys (TYPE_1__*) ; 

__attribute__((used)) static int
my_list_rx_init(struct my_softc * sc)
{
	struct my_chain_data *cd;
	struct my_list_data *ld;
	int             i;

	MY_LOCK_ASSERT(sc);
	cd = &sc->my_cdata;
	ld = sc->my_ldata;
	for (i = 0; i < MY_RX_LIST_CNT; i++) {
		cd->my_rx_chain[i].my_ptr =
		    (struct my_desc *) & ld->my_rx_list[i];
		if (my_newbuf(sc, &cd->my_rx_chain[i]) == ENOBUFS) {
			MY_UNLOCK(sc);
			return (ENOBUFS);
		}
		if (i == (MY_RX_LIST_CNT - 1)) {
			cd->my_rx_chain[i].my_nextdesc = &cd->my_rx_chain[0];
			ld->my_rx_list[i].my_next = vtophys(&ld->my_rx_list[0]);
		} else {
			cd->my_rx_chain[i].my_nextdesc =
			    &cd->my_rx_chain[i + 1];
			ld->my_rx_list[i].my_next =
			    vtophys(&ld->my_rx_list[i + 1]);
		}
	}
	cd->my_rx_head = &cd->my_rx_chain[0];
	return (0);
}