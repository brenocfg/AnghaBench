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
struct intr_vector {struct fire_icarg* iv_icarg; } ;
struct fire_softc {int dummy; } ;
struct fire_icarg {int /*<<< orphan*/  fica_map; struct fire_softc* fica_sc; } ;

/* Variables and functions */
 int FIRE_PCI_READ_8 (struct fire_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (struct fire_softc*,int /*<<< orphan*/ ,int) ; 
 int FO_PCI_IMAP_V ; 

__attribute__((used)) static void
fire_intr_disable(void *arg)
{
	struct intr_vector *iv;
	struct fire_icarg *fica;
	struct fire_softc *sc;

	iv = arg;
	fica = iv->iv_icarg;
	sc = fica->fica_sc;
	FIRE_PCI_WRITE_8(sc, fica->fica_map,
	    FIRE_PCI_READ_8(sc, fica->fica_map) & ~FO_PCI_IMAP_V);
}