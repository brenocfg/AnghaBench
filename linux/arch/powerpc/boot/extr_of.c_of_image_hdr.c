#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* e_ident; } ;
typedef  TYPE_1__ Elf64_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ PROG_START ; 
 scalar_t__ claim_base ; 

__attribute__((used)) static void of_image_hdr(const void *hdr)
{
	const Elf64_Ehdr *elf64 = hdr;

	if (elf64->e_ident[EI_CLASS] == ELFCLASS64) {
		/*
		 * Maintain a "magic" minimum address. This keeps some older
		 * firmware platforms running.
		 */
		if (claim_base < PROG_START)
			claim_base = PROG_START;
	}
}