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
 int /*<<< orphan*/  blast_dcache64_page (unsigned long) ; 

__attribute__((used)) static inline void r4k_blast_dcache_page_dc64(unsigned long addr)
{
	blast_dcache64_page(addr);
}