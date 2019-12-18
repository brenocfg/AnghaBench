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
 unsigned long P1SEG ; 
 unsigned long P3SEG ; 

__attribute__((used)) static inline bool pmb_addr_valid(unsigned long addr, unsigned long size)
{
	return (addr >= P1SEG && (addr + size - 1) < P3SEG);
}