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
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 s32_gte(s32 a, s32 b) {
  a -= b;
  /* a >= 0 iff a >= b. */
  return ~(a >> 31);
}