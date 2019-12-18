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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dcons_crom_softc {int /*<<< orphan*/  unit; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_HI (int) ; 
 int /*<<< orphan*/  ADDR_LO (int) ; 
 int /*<<< orphan*/  DCONS_CSR_KEY_RESET_HI ; 
 int /*<<< orphan*/  DCONS_CSR_KEY_RESET_LO ; 
 scalar_t__ KERNBASE ; 
 int /*<<< orphan*/  crom_add_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ idt ; 
 scalar_t__ pmap_kextract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dcons_crom_expose_idt(struct dcons_crom_softc *sc)
{
	static off_t idt_paddr;

	/* XXX */
#ifdef __amd64__
	idt_paddr = (char *)idt - (char *)KERNBASE;
#else /* __i386__ */
	idt_paddr = (off_t)pmap_kextract((vm_offset_t)idt);
#endif

	crom_add_entry(&sc->unit, DCONS_CSR_KEY_RESET_HI, ADDR_HI(idt_paddr));
	crom_add_entry(&sc->unit, DCONS_CSR_KEY_RESET_LO, ADDR_LO(idt_paddr));
}