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
struct restore_data_record {scalar_t__ magic; int /*<<< orphan*/  e820_digest; int /*<<< orphan*/  cr3; int /*<<< orphan*/  jump_address_phys; int /*<<< orphan*/  jump_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ RESTORE_MAGIC ; 
 scalar_t__ hibernation_e820_mismatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_address_phys ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  restore_cr3 ; 
 int /*<<< orphan*/  restore_jump_address ; 

int arch_hibernation_header_restore(void *addr)
{
	struct restore_data_record *rdr = addr;

	if (rdr->magic != RESTORE_MAGIC) {
		pr_crit("Unrecognized hibernate image header format!\n");
		return -EINVAL;
	}

	restore_jump_address = rdr->jump_address;
	jump_address_phys = rdr->jump_address_phys;
	restore_cr3 = rdr->cr3;

	if (hibernation_e820_mismatch(rdr->e820_digest)) {
		pr_crit("Hibernate inconsistent memory map detected!\n");
		return -ENODEV;
	}

	return 0;
}