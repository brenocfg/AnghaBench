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
typedef  char u8 ;

/* Variables and functions */

u8 lotus64_to_int (const u8 c)
{
  if ((c >= '0') && (c <= '9')) return c - '0';
  if ((c >= 'A') && (c <= 'Z')) return c - 'A' + 10;
  if ((c >= 'a') && (c <= 'z')) return c - 'a' + 36;
  if (c == '+') return 62;
  if (c == '/') return 63;

  return 0;
}