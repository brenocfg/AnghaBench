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
struct nfe_softc {scalar_t__ nfe_msi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_IRQ_MASK ; 
 int /*<<< orphan*/  NFE_IRQ_WANTED ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfe_set_intr(struct nfe_softc *sc)
{

	if (sc->nfe_msi != 0)
		NFE_WRITE(sc, NFE_IRQ_MASK, NFE_IRQ_WANTED);
}