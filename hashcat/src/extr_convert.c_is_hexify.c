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
 int is_valid_hex_string (char const*,size_t const) ; 

bool is_hexify (const u8 *buf, const size_t len)
{
  if (len < 6) return false; // $HEX[] = 6

  // length of the hex string must be a multiple of 2
  // and the length of "$HEX[]" is 6 (also an even length)
  // Therefore the overall length must be an even number:

  if ((len & 1) == 1) return false;

  if (buf[0]       != '$') return (false);
  if (buf[1]       != 'H') return (false);
  if (buf[2]       != 'E') return (false);
  if (buf[3]       != 'X') return (false);
  if (buf[4]       != '[') return (false);
  if (buf[len - 1] != ']') return (false);

  if (is_valid_hex_string (buf + 5, len - 6) == false) return false;

  return true;
}