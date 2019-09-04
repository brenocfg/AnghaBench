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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int is_valid_base64c_char (int /*<<< orphan*/  const) ; 

bool is_valid_base64c_string (const u8 *s, const size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    const u8 c = s[i];

    if (is_valid_base64c_char (c) == false) return false;
  }

  return true;
}