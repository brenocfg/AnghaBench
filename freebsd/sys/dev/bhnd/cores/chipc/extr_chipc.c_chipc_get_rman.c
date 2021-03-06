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
struct rman {int dummy; } ;
struct chipc_softc {struct rman mem_rman; } ;

/* Variables and functions */
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 

__attribute__((used)) static struct rman *
chipc_get_rman(struct chipc_softc *sc, int type)
{	
	switch (type) {
	case SYS_RES_MEMORY:
		return (&sc->mem_rman);

	case SYS_RES_IRQ:
		/* We delegate IRQ resource management to the parent bus */
		return (NULL);

	default:
		return (NULL);
	};
}