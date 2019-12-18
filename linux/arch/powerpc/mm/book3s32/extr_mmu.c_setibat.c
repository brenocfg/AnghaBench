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
struct ppc_bat {unsigned long batu; int batl; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 struct ppc_bat** BATS ; 
 int BAT_PHYS_ADDR (int /*<<< orphan*/ ) ; 
 unsigned long BPP_RX ; 
 unsigned long BPP_XX ; 
 int /*<<< orphan*/  CPU_FTR_NEED_COHERENT ; 
 unsigned long _PAGE_COHERENT ; 
 scalar_t__ _PAGE_EXEC ; 
 unsigned long _PAGE_USER ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setibat(int index, unsigned long virt, phys_addr_t phys,
		    unsigned int size, pgprot_t prot)
{
	unsigned int bl = (size >> 17) - 1;
	int wimgxpp;
	struct ppc_bat *bat = BATS[index];
	unsigned long flags = pgprot_val(prot);

	if (!cpu_has_feature(CPU_FTR_NEED_COHERENT))
		flags &= ~_PAGE_COHERENT;

	wimgxpp = (flags & _PAGE_COHERENT) | (_PAGE_EXEC ? BPP_RX : BPP_XX);
	bat[0].batu = virt | (bl << 2) | 2; /* Vs=1, Vp=0 */
	bat[0].batl = BAT_PHYS_ADDR(phys) | wimgxpp;
	if (flags & _PAGE_USER)
		bat[0].batu |= 1;	/* Vp = 1 */
}