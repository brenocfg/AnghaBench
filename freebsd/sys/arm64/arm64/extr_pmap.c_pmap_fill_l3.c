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
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 scalar_t__ L3_SIZE ; 
 int Ln_ENTRIES ; 

__attribute__((used)) static void
pmap_fill_l3(pt_entry_t *firstl3, pt_entry_t newl3)
{
	pt_entry_t *l3;

	for (l3 = firstl3; l3 - firstl3 < Ln_ENTRIES; l3++) {
		*l3 = newl3;
		newl3 += L3_SIZE;
	}
}