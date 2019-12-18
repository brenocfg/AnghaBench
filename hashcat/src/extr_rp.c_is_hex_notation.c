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
typedef  int u32 ;

/* Variables and functions */
 int is_valid_hex_char (char const) ; 

bool is_hex_notation (const char *rule_buf, u32 rule_len, u32 rule_pos)
{
  if ((rule_pos + 4) > rule_len) return false;

  if (rule_buf[rule_pos + 0] != '\\') return false;
  if (rule_buf[rule_pos + 1] != 'x')  return false;

  if (is_valid_hex_char (rule_buf[rule_pos + 2]) == false) return false;
  if (is_valid_hex_char (rule_buf[rule_pos + 3]) == false) return false;

  return true;
}