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

/* Variables and functions */
 scalar_t__ memory_limit ; 
 scalar_t__ next_free ; 

char *
sbrk (int amount)
{
  if (next_free + amount > memory_limit)
    return (char *) -1;
  next_free += amount;
  return next_free - amount;
}