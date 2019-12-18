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
#define  MMU_PAGE_16M 129 
#define  MMU_PAGE_64K 128 

__attribute__((used)) static int mmu_pagesize(int mmu_pg)
{
	switch (mmu_pg) {
	case MMU_PAGE_64K:
		return 16;
	case MMU_PAGE_16M:
		return 24;
	}
	return 12;
}