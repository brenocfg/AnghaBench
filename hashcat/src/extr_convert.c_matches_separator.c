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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static bool matches_separator (const u8 *buf, const size_t len, const char separator)
{
  for (size_t i = 0; i < len; i++)
  {
    const char c = (char) buf[i];

    if (c == separator) return true;
  }

  return false;
}