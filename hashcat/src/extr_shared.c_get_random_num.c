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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ rand () ; 
 scalar_t__ random () ; 

u32 get_random_num (const u32 min, const u32 max)
{
  if (min == max) return (min);

  const u32 low = max - min;

  if (low == 0) return (0);

  #if defined (_WIN)

  return (((u32) rand () % (max - min)) + min);

  #else

  return (((u32) random () % (max - min)) + min);

  #endif
}