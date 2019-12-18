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
 unsigned long HI_OBP_ADDRESS ; 
 unsigned long LOW_OBP_ADDRESS ; 

__attribute__((used)) static inline int in_obp_range(unsigned long vaddr)
{
	return (vaddr >= LOW_OBP_ADDRESS &&
		vaddr < HI_OBP_ADDRESS);
}