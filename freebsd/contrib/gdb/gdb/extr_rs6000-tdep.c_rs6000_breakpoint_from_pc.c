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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 

__attribute__((used)) const static unsigned char *
rs6000_breakpoint_from_pc (CORE_ADDR *bp_addr, int *bp_size)
{
  static unsigned char big_breakpoint[] = { 0x7d, 0x82, 0x10, 0x08 };
  static unsigned char little_breakpoint[] = { 0x08, 0x10, 0x82, 0x7d };
  *bp_size = 4;
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    return big_breakpoint;
  else
    return little_breakpoint;
}