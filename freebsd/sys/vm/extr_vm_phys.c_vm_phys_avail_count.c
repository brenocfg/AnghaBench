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
 int PHYS_AVAIL_ENTRIES ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__* phys_avail ; 

__attribute__((used)) static int
vm_phys_avail_count(void)
{
	int i;

	for (i = 0; phys_avail[i + 1]; i += 2)
		continue;
	if (i > PHYS_AVAIL_ENTRIES)
		panic("Improperly terminated phys_avail %d entries", i);

	return (i);
}