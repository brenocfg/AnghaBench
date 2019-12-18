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
struct thunder_pem_softc {struct rman mem_rman; struct rman io_rman; } ;

/* Variables and functions */
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 

__attribute__((used)) static struct rman *
thunder_pem_rman(struct thunder_pem_softc *sc, int type)
{

	switch (type) {
	case SYS_RES_IOPORT:
		return (&sc->io_rman);
	case SYS_RES_MEMORY:
		return (&sc->mem_rman);
	default:
		break;
	}

	return (NULL);
}