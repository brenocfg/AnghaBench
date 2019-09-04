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

bool is_valid_base64b_char (const u8 c)
{
  if ((c >= '0') && (c <= '9')) return true;
  if ((c >= 'A') && (c <= 'Z')) return true;
  if ((c >= 'a') && (c <= 'z')) return true;

  if (c == '.') return true;
  if (c == '/') return true;
  if (c == '=') return true;

  return false;
}