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
typedef  int /*<<< orphan*/  breakpoint ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *
s390_breakpoint_from_pc (CORE_ADDR *pcptr, int *lenptr)
{
  static unsigned char breakpoint[] = { 0x0, 0x1 };

  *lenptr = sizeof (breakpoint);
  return breakpoint;
}