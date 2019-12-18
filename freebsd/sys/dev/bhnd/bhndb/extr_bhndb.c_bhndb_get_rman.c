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
struct rman {int dummy; } ;
struct bhndb_softc {TYPE_1__* bus_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct rman br_irq_rman; struct rman br_mem_rman; struct rman ht_mem_rman; } ;

/* Variables and functions */
#define  BHNDB_ADDRSPACE_BRIDGED 131 
#define  BHNDB_ADDRSPACE_NATIVE 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int bhndb_get_addrspace (struct bhndb_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rman *
bhndb_get_rman(struct bhndb_softc *sc, device_t child, int type)
{	
	switch (bhndb_get_addrspace(sc, child)) {
	case BHNDB_ADDRSPACE_NATIVE:
		switch (type) {
		case SYS_RES_MEMORY:
			return (&sc->bus_res->ht_mem_rman);
		case SYS_RES_IRQ:
			return (NULL);
		default:
			return (NULL);
		}
		
	case BHNDB_ADDRSPACE_BRIDGED:
		switch (type) {
		case SYS_RES_MEMORY:
			return (&sc->bus_res->br_mem_rman);
		case SYS_RES_IRQ:
			return (&sc->bus_res->br_irq_rman);
		default:
			return (NULL);
		}
	}

	/* Quieten gcc */
	return (NULL);
}