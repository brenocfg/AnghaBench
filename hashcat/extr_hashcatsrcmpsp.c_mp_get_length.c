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
 size_t strlen (char const*) ; 

u32 mp_get_length (const char *mask)
{
  u32 len = 0;

  const size_t mask_len = strlen (mask);

  for (size_t i = 0; i < mask_len; i++)
  {
    if (mask[i] == '?') i++;

    len++;
  }

  return len;
}