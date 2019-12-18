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

size_t superchop_with_length (char *buf, const size_t len)
{
  size_t new_len = len;

  while (new_len)
  {
    if (buf[new_len - 1] == '\n')
    {
      new_len--;

      buf[new_len] = 0;

      continue;
    }

    if (buf[new_len - 1] == '\r')
    {
      new_len--;

      buf[new_len] = 0;

      continue;
    }

    break;
  }

  return new_len;
}