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
typedef  scalar_t__ bit ;

/* Variables and functions */
 scalar_t__ MSB_SET (unsigned long) ; 

unsigned long
_divulong (unsigned long a, unsigned long b)
{
  unsigned long reste = 0L;
  unsigned char count = 32;
  #if defined(SDCC_STACK_AUTO) || defined(SDCC_z80)
    char c;
  #else
    bit c;
  #endif

  do
  {
    // reste: a <- 0;
    c = MSB_SET(a);
    a <<= 1;
    reste <<= 1;
    if (c)
      reste |= 1L;

    if (reste >= b)
    {
      reste -= b;
      // a <- (result = 1)
      a |= 1L;
    }
  }
  while (--count);
  return a;
}