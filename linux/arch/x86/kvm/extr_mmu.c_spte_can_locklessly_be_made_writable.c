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
typedef  int u64 ;

/* Variables and functions */
 int SPTE_HOST_WRITEABLE ; 
 int SPTE_MMU_WRITEABLE ; 

__attribute__((used)) static bool spte_can_locklessly_be_made_writable(u64 spte)
{
	return (spte & (SPTE_HOST_WRITEABLE | SPTE_MMU_WRITEABLE)) ==
		(SPTE_HOST_WRITEABLE | SPTE_MMU_WRITEABLE);
}