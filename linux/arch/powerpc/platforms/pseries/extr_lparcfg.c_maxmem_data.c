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
struct seq_file {int dummy; } ;
struct TYPE_2__ {unsigned long n_lmbs; unsigned long lmb_size; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 TYPE_1__* drmem_info ; 
 unsigned long hugetlb_total_pages () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 

__attribute__((used)) static void maxmem_data(struct seq_file *m)
{
	unsigned long maxmem = 0;

	maxmem += drmem_info->n_lmbs * drmem_info->lmb_size;
	maxmem += hugetlb_total_pages() * PAGE_SIZE;

	seq_printf(m, "MaxMem=%ld\n", maxmem);
}