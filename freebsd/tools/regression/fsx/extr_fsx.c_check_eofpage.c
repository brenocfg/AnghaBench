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
 unsigned int file_size ; 
 unsigned int page_mask ; 
 uintptr_t page_size ; 
 int /*<<< orphan*/  prt (char*,char*,unsigned int,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_failure (int) ; 
 int /*<<< orphan*/  short_at (uintptr_t) ; 

void
check_eofpage(char *s, unsigned offset, char *p, int size)
{
	uintptr_t last_page, should_be_zero;

	if (offset + size <= (file_size & ~page_mask))
		return;
	/*
	 * we landed in the last page of the file
	 * test to make sure the VM system provided 0's 
	 * beyond the true end of the file mapping
	 * (as required by mmap def in 1996 posix 1003.1)
	 */
	last_page = ((uintptr_t)p + (offset & page_mask) + size) & ~page_mask;

	for (should_be_zero = last_page + (file_size & page_mask);
	     should_be_zero < last_page + page_size;
	     should_be_zero++)
		if (*(char *)should_be_zero) {
			prt("Mapped %s: non-zero data past EOF (0x%llx) page offset 0x%x is 0x%04x\n",
			    s, file_size - 1, should_be_zero & page_mask,
			    short_at(should_be_zero));
			report_failure(205);
		}
}