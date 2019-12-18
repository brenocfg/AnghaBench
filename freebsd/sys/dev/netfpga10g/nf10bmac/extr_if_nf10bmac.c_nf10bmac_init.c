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
struct nf10bmac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF10BMAC_LOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_UNLOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_init_locked (struct nf10bmac_softc*) ; 

__attribute__((used)) static void
nf10bmac_init(void *xsc)
{
	struct nf10bmac_softc *sc;

	sc = (struct nf10bmac_softc *)xsc;
	NF10BMAC_LOCK(sc);
	nf10bmac_init_locked(sc);
	NF10BMAC_UNLOCK(sc);
}