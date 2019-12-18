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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long SUN3_PAGE_ACCESSED ; 
 unsigned long SUN3_PAGE_MODIFIED ; 
 unsigned long SUN3_PAGE_NOCACHE ; 
 unsigned long SUN3_PAGE_PGNUM_MASK ; 
 unsigned long SUN3_PAGE_SYSTEM ; 
#define  SUN3_PAGE_TYPE_IO 131 
 unsigned long SUN3_PAGE_TYPE_MASK ; 
#define  SUN3_PAGE_TYPE_MEMORY 130 
#define  SUN3_PAGE_TYPE_VME16 129 
#define  SUN3_PAGE_TYPE_VME32 128 
 unsigned long SUN3_PAGE_VALID ; 
 unsigned long SUN3_PAGE_WRITEABLE ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 

void print_pte (pte_t pte)
{
#if 0
	/* Verbose version. */
	unsigned long val = pte_val (pte);
	pr_cont(" pte=%lx [addr=%lx",
		val, (val & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT);
	if (val & SUN3_PAGE_VALID)	pr_cont(" valid");
	if (val & SUN3_PAGE_WRITEABLE)	pr_cont(" write");
	if (val & SUN3_PAGE_SYSTEM)	pr_cont(" sys");
	if (val & SUN3_PAGE_NOCACHE)	pr_cont(" nocache");
	if (val & SUN3_PAGE_ACCESSED)	pr_cont(" accessed");
	if (val & SUN3_PAGE_MODIFIED)	pr_cont(" modified");
	switch (val & SUN3_PAGE_TYPE_MASK) {
		case SUN3_PAGE_TYPE_MEMORY: pr_cont(" memory"); break;
		case SUN3_PAGE_TYPE_IO:     pr_cont(" io");     break;
		case SUN3_PAGE_TYPE_VME16:  pr_cont(" vme16");  break;
		case SUN3_PAGE_TYPE_VME32:  pr_cont(" vme32");  break;
	}
	pr_cont("]\n");
#else
	/* Terse version. More likely to fit on a line. */
	unsigned long val = pte_val (pte);
	char flags[7], *type;

	flags[0] = (val & SUN3_PAGE_VALID)     ? 'v' : '-';
	flags[1] = (val & SUN3_PAGE_WRITEABLE) ? 'w' : '-';
	flags[2] = (val & SUN3_PAGE_SYSTEM)    ? 's' : '-';
	flags[3] = (val & SUN3_PAGE_NOCACHE)   ? 'x' : '-';
	flags[4] = (val & SUN3_PAGE_ACCESSED)  ? 'a' : '-';
	flags[5] = (val & SUN3_PAGE_MODIFIED)  ? 'm' : '-';
	flags[6] = '\0';

	switch (val & SUN3_PAGE_TYPE_MASK) {
		case SUN3_PAGE_TYPE_MEMORY: type = "memory"; break;
		case SUN3_PAGE_TYPE_IO:     type = "io"    ; break;
		case SUN3_PAGE_TYPE_VME16:  type = "vme16" ; break;
		case SUN3_PAGE_TYPE_VME32:  type = "vme32" ; break;
		default: type = "unknown?"; break;
	}

	pr_cont(" pte=%08lx [%07lx %s %s]\n",
		val, (val & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT, flags, type);
#endif
}