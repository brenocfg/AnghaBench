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
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ u_int ;
struct pcpu {unsigned long long pc_mid; int pc_cpuid; } ;
struct intr_vector {unsigned long long iv_mid; struct fire_icarg* iv_icarg; } ;
struct fire_softc {scalar_t__ sc_mode; } ;
struct fire_icarg {int /*<<< orphan*/  fica_map; struct fire_softc* fica_sc; } ;

/* Variables and functions */
 scalar_t__ FIRE_MODE_OBERON ; 
 unsigned long long FIRE_PCI_IMAP_T_JPID_MASK ; 
 unsigned long long FIRE_PCI_IMAP_T_JPID_SHFT ; 
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (struct fire_softc*,int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long FO_PCI_IMAP_INT_CTRL_NUM_MASK ; 
 unsigned long long FO_PCI_IMAP_INT_CTRL_NUM_SHFT ; 
 unsigned long long FO_PCI_IMAP_V ; 
 unsigned long long OBERON_PCI_IMAP_T_DESTID_MASK ; 
 unsigned long long OBERON_PCI_IMAP_T_DESTID_SHFT ; 
 scalar_t__ mp_ncpus ; 
 struct pcpu* pcpu_find (scalar_t__) ; 

__attribute__((used)) static void
fire_intr_enable(void *arg)
{
	struct intr_vector *iv;
	struct fire_icarg *fica;
	struct fire_softc *sc;
	struct pcpu *pc;
	uint64_t mr;
	u_int ctrl, i;

	iv = arg;
	fica = iv->iv_icarg;
	sc = fica->fica_sc;
	mr = FO_PCI_IMAP_V;
	if (sc->sc_mode == FIRE_MODE_OBERON)
		mr |= (iv->iv_mid << OBERON_PCI_IMAP_T_DESTID_SHFT) &
		    OBERON_PCI_IMAP_T_DESTID_MASK;
	else
		mr |= (iv->iv_mid << FIRE_PCI_IMAP_T_JPID_SHFT) &
		    FIRE_PCI_IMAP_T_JPID_MASK;
	/*
	 * Given that all mondos for the same target are required to use the
	 * same interrupt controller we just use the CPU ID for indexing the
	 * latter.
	 */
	ctrl = 0;
	for (i = 0; i < mp_ncpus; ++i) {
		pc = pcpu_find(i);
		if (pc == NULL || iv->iv_mid != pc->pc_mid)
			continue;
		ctrl = pc->pc_cpuid % 4;
		break;
	}
	mr |= (1ULL << ctrl) << FO_PCI_IMAP_INT_CTRL_NUM_SHFT &
	    FO_PCI_IMAP_INT_CTRL_NUM_MASK;
	FIRE_PCI_WRITE_8(sc, fica->fica_map, mr);
}