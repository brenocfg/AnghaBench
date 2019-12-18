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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned (unsigned long*) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline int dwarf_read_addr(unsigned long *src, unsigned long *dst)
{
	u32 val = get_unaligned(src);
	put_unaligned(val, dst);
	return sizeof(unsigned long *);
}