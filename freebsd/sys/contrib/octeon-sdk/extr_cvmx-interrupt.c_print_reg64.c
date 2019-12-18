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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ HI32 (int /*<<< orphan*/ ) ; 
 scalar_t__ LO32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_safe_printf (char*,char const*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void print_reg64(const char *name, uint64_t reg)
{
    cvmx_safe_printf("%16s: 0x%08x%08x\n", name, (unsigned int)HI32(reg),(unsigned int)LO32(reg));
}