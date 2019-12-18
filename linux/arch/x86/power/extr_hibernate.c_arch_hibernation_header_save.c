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
struct restore_data_record {unsigned long jump_address; int cr3; int /*<<< orphan*/  e820_digest; int /*<<< orphan*/  jump_address_phys; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int CR3_PCID_MASK ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  RESTORE_MAGIC ; 
 int /*<<< orphan*/  __pa_symbol (scalar_t__) ; 
 int hibernation_e820_save (int /*<<< orphan*/ ) ; 
 int restore_cr3 ; 
 scalar_t__ restore_registers ; 

int arch_hibernation_header_save(void *addr, unsigned int max_size)
{
	struct restore_data_record *rdr = addr;

	if (max_size < sizeof(struct restore_data_record))
		return -EOVERFLOW;
	rdr->magic = RESTORE_MAGIC;
	rdr->jump_address = (unsigned long)restore_registers;
	rdr->jump_address_phys = __pa_symbol(restore_registers);

	/*
	 * The restore code fixes up CR3 and CR4 in the following sequence:
	 *
	 * [in hibernation asm]
	 * 1. CR3 <= temporary page tables
	 * 2. CR4 <= mmu_cr4_features (from the kernel that restores us)
	 * 3. CR3 <= rdr->cr3
	 * 4. CR4 <= mmu_cr4_features (from us, i.e. the image kernel)
	 * [in restore_processor_state()]
	 * 5. CR4 <= saved CR4
	 * 6. CR3 <= saved CR3
	 *
	 * Our mmu_cr4_features has CR4.PCIDE=0, and toggling
	 * CR4.PCIDE while CR3's PCID bits are nonzero is illegal, so
	 * rdr->cr3 needs to point to valid page tables but must not
	 * have any of the PCID bits set.
	 */
	rdr->cr3 = restore_cr3 & ~CR3_PCID_MASK;

	return hibernation_e820_save(rdr->e820_digest);
}