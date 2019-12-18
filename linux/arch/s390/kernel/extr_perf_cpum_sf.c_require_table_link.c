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
 unsigned long CPUM_SF_SDBT_TL_OFFSET ; 
 unsigned long PAGE_MASK ; 

__attribute__((used)) static inline int require_table_link(const void *sdbt)
{
	return ((unsigned long) sdbt & ~PAGE_MASK) == CPUM_SF_SDBT_TL_OFFSET;
}