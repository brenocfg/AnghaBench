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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

int memcmp(const void *va, const void *vb, size_t len)
{
  const uint8_t *a = va, *b = vb;

  for (size_t i = 0; i < len; i++)
  {
    if (a[i] != b[i])
      return a[i] < b[i] ? -1 : 1;
  }

  return 0;
}