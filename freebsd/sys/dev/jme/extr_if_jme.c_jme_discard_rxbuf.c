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
struct TYPE_2__ {struct jme_desc* jme_rx_ring; } ;
struct jme_softc {TYPE_1__ jme_rdata; } ;
struct jme_desc {void* buflen; void* flags; } ;

/* Variables and functions */
 int JME_RD_64BIT ; 
 int JME_RD_INTR ; 
 int JME_RD_OWN ; 
 int MCLBYTES ; 
 void* htole32 (int) ; 

__attribute__((used)) static __inline void
jme_discard_rxbuf(struct jme_softc *sc, int cons)
{
	struct jme_desc *desc;

	desc = &sc->jme_rdata.jme_rx_ring[cons];
	desc->flags = htole32(JME_RD_OWN | JME_RD_INTR | JME_RD_64BIT);
	desc->buflen = htole32(MCLBYTES);
}