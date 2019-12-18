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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int set_memory_decrypted (unsigned long,unsigned int) ; 
 scalar_t__ sev_active () ; 

int arch_kexec_post_alloc_pages(void *vaddr, unsigned int pages, gfp_t gfp)
{
	if (sev_active())
		return 0;

	/*
	 * If SME is active we need to be sure that kexec pages are
	 * not encrypted because when we boot to the new kernel the
	 * pages won't be accessed encrypted (initially).
	 */
	return set_memory_decrypted((unsigned long)vaddr, pages);
}