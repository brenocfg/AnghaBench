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
typedef  int u16 ;
struct bce_softc {TYPE_1__* status_block; } ;
struct TYPE_2__ {int status_rx_quick_consumer_index0; } ;

/* Variables and functions */
 int USABLE_RX_BD_PER_PAGE ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline u16
bce_get_hw_rx_cons(struct bce_softc *sc)
{
	u16 hw_cons;

	rmb();
	hw_cons = sc->status_block->status_rx_quick_consumer_index0;
	if ((hw_cons & USABLE_RX_BD_PER_PAGE) == USABLE_RX_BD_PER_PAGE)
		hw_cons++;

	return hw_cons;
}