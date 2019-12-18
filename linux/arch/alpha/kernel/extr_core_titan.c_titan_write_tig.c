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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 unsigned long* mk_tig_addr (int) ; 

__attribute__((used)) static inline void 
titan_write_tig(int offset, u8 value)
{
	volatile unsigned long *tig_addr = mk_tig_addr(offset);
	*tig_addr = (unsigned long)value;
}