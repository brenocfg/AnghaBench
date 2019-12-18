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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  rxl; int /*<<< orphan*/  rate; } ;
struct sbni_softc {size_t cur_rxl_index; scalar_t__ enaddr; int /*<<< orphan*/  maxframe; TYPE_1__ csr1; scalar_t__ delta_rxl; } ;
struct sbni_flags {size_t rxl; int mac_addr; int /*<<< orphan*/  rate; scalar_t__ fixed_rate; scalar_t__ fixed_rxl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FRAME_LEN ; 
 int /*<<< orphan*/  DEFAULT_RATE ; 
 size_t DEF_RXL ; 
 scalar_t__ DEF_RXL_DELTA ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  read_random (scalar_t__,int) ; 
 int /*<<< orphan*/ * rxl_tab ; 

__attribute__((used)) static void
set_initial_values(struct sbni_softc *sc, struct sbni_flags flags)
{
	if (flags.fixed_rxl) {
		sc->delta_rxl = 0; /* disable receive level autodetection */
		sc->cur_rxl_index = flags.rxl;
	} else {
		sc->delta_rxl = DEF_RXL_DELTA;
		sc->cur_rxl_index = DEF_RXL;
	}
   
	sc->csr1.rate = flags.fixed_rate ? flags.rate : DEFAULT_RATE;
	sc->csr1.rxl  = rxl_tab[sc->cur_rxl_index];
	sc->maxframe  = DEFAULT_FRAME_LEN;
   
	/*
	 * generate Ethernet address (0x00ff01xxxxxx)
	 */
	*(u_int16_t *) sc->enaddr = htons(0x00ff);
	if (flags.mac_addr) {
		*(u_int32_t *) (sc->enaddr + 2) =
		    htonl(flags.mac_addr | 0x01000000);
	} else {
		*(u_char *) (sc->enaddr + 2) = 0x01;
		read_random(sc->enaddr + 3, 3);
	}
}