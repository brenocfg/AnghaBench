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
typedef  int uint64_t ;
struct intr_vector {struct fire_icarg* iv_icarg; } ;
struct fire_softc {int dummy; } ;
struct fire_icarg {int /*<<< orphan*/  fica_clr; int /*<<< orphan*/  fica_map; struct fire_softc* fica_sc; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  FIRE_PCI_BARRIER (struct fire_softc*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ FIRE_PCI_READ_8 (struct fire_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (struct fire_softc*,int /*<<< orphan*/ ,int) ; 
 int FO_PCI_IMAP_V ; 
 scalar_t__ INTCLR_IDLE ; 
 int /*<<< orphan*/  fire_intr_enable (void*) ; 

__attribute__((used)) static void
fire_intr_assign(void *arg)
{
	struct intr_vector *iv;
	struct fire_icarg *fica;
	struct fire_softc *sc;
	uint64_t mr;

	iv = arg;
	fica = iv->iv_icarg;
	sc = fica->fica_sc;
	mr = FIRE_PCI_READ_8(sc, fica->fica_map);
	if ((mr & FO_PCI_IMAP_V) != 0) {
		FIRE_PCI_WRITE_8(sc, fica->fica_map, mr & ~FO_PCI_IMAP_V);
		FIRE_PCI_BARRIER(sc, fica->fica_map, 8,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	}
	while (FIRE_PCI_READ_8(sc, fica->fica_clr) != INTCLR_IDLE)
		;
	if ((mr & FO_PCI_IMAP_V) != 0)
		fire_intr_enable(arg);
}