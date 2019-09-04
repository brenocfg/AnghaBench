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
 scalar_t__ isdigit (int const) ; 
 size_t strlen (char const*) ; 

bool hc_string_is_digit (const char *s)
{
  if (s == NULL) return false;

  const size_t len = strlen (s);

  if (len == 0) return false;

  for (size_t i = 0; i < len; i++)
  {
    const int c = (const int) s[i];

    if (isdigit (c) == 0) return false;
  }

  return true;
}