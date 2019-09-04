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
typedef  scalar_t__ const u32 ;

/* Variables and functions */

u32 round_up_multiple_32 (const u32 v, const u32 m)
{
  if (m == 0) return v;

  const u32 r = v % m;

  if (r == 0) return v;

  return v + m - r;
}