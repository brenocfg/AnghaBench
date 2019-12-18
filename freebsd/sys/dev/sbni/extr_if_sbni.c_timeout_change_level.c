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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  rxl; } ;
struct sbni_softc {size_t cur_rxl_index; size_t timeout_rxl; scalar_t__ cur_rxl_rcvd; scalar_t__ prev_rxl_rcvd; TYPE_1__ csr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR0 ; 
 int /*<<< orphan*/  CSR1 ; 
 int /*<<< orphan*/ * rxl_tab ; 
 int /*<<< orphan*/  sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* timeout_rxl_tab ; 

__attribute__((used)) static void
timeout_change_level(struct sbni_softc *sc)
{
	sc->cur_rxl_index = timeout_rxl_tab[sc->timeout_rxl];
	if (++sc->timeout_rxl >= 4)
		sc->timeout_rxl = 0;

	sc->csr1.rxl = rxl_tab[sc->cur_rxl_index];
	sbni_inb(sc, CSR0);
	sbni_outb(sc, CSR1, *(u_char *)&sc->csr1);

	sc->prev_rxl_rcvd = sc->cur_rxl_rcvd;
	sc->cur_rxl_rcvd  = 0;
}