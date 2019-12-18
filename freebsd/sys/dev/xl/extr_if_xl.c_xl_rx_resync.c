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
struct TYPE_4__ {struct xl_chain_onefrag* xl_rx_head; } ;
struct xl_softc {TYPE_2__ xl_cdata; } ;
struct xl_chain_onefrag {struct xl_chain_onefrag* xl_next; TYPE_1__* xl_ptr; } ;
struct TYPE_3__ {scalar_t__ xl_status; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_RX_LIST_CNT ; 

__attribute__((used)) static int
xl_rx_resync(struct xl_softc *sc)
{
	struct xl_chain_onefrag	*pos;
	int			i;

	XL_LOCK_ASSERT(sc);

	pos = sc->xl_cdata.xl_rx_head;

	for (i = 0; i < XL_RX_LIST_CNT; i++) {
		if (pos->xl_ptr->xl_status)
			break;
		pos = pos->xl_next;
	}

	if (i == XL_RX_LIST_CNT)
		return (0);

	sc->xl_cdata.xl_rx_head = pos;

	return (EAGAIN);
}