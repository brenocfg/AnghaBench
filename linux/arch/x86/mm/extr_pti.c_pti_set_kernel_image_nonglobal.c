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

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PFN_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMD_PAGE_SIZE ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  _text ; 
 int /*<<< orphan*/  set_memory_nonglobal (unsigned long,unsigned long) ; 

__attribute__((used)) static void pti_set_kernel_image_nonglobal(void)
{
	/*
	 * The identity map is created with PMDs, regardless of the
	 * actual length of the kernel.  We need to clear
	 * _PAGE_GLOBAL up to a PMD boundary, not just to the end
	 * of the image.
	 */
	unsigned long start = PFN_ALIGN(_text);
	unsigned long end = ALIGN((unsigned long)_end, PMD_PAGE_SIZE);

	/*
	 * This clears _PAGE_GLOBAL from the entire kernel image.
	 * pti_clone_kernel_text() map put _PAGE_GLOBAL back for
	 * areas that are mapped to userspace.
	 */
	set_memory_nonglobal(start, (end - start) >> PAGE_SHIFT);
}