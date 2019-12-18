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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t xgetbv(uint32_t xcr)
{
  uint32_t a, d;
  __asm__ __volatile__(
    "xgetbv"
    :  "=a"(a),"=d"(d)
    : "c"(xcr)
  );
  return ((uint64_t)d << 32) | a;
}