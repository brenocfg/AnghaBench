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
typedef  uintptr_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t ocs_addr32_lo(uintptr_t addr)
{
#if defined(__LP64__)
	return (uint32_t)(addr & 0xffffffffUL);
#else
	return addr;
#endif
}