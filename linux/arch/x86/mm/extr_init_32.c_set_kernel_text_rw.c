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
 unsigned long PAGE_SHIFT ; 
 unsigned long PFN_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _etext ; 
 int /*<<< orphan*/  _text ; 
 int /*<<< orphan*/  kernel_set_to_readonly ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_pages_rw (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void set_kernel_text_rw(void)
{
	unsigned long start = PFN_ALIGN(_text);
	unsigned long size = PFN_ALIGN(_etext) - start;

	if (!kernel_set_to_readonly)
		return;

	pr_debug("Set kernel text: %lx - %lx for read write\n",
		 start, start+size);

	set_pages_rw(virt_to_page(start), size >> PAGE_SHIFT);
}