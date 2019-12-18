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
typedef  int /*<<< orphan*/  vaddr_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t
mips_ioread_uint8(vaddr_t vaddr)
{
	uint8_t v;

	__asm__ __volatile__ ("lb %0, 0(%1)" : "=r" (v) : "r" (vaddr));
	return (v);
}