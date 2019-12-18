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

__attribute__((used)) static char
sign_bits(int base, const char *p)
{
  char c;

  switch (base) {
  case 16:
    if (*p == 'X') c = 'F';
    else c = 'f';
    break;
  case 8:
    c = '7'; break;
  case 2:
    c = '1'; break;
  default:
    c = '.'; break;
  }
  return c;
}