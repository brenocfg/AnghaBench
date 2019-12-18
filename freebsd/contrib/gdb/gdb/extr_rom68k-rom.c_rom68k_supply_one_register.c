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
typedef  int ULONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int hex_digit_value (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hex_digit (unsigned char) ; 
 scalar_t__ is_whitespace (unsigned char) ; 
 int /*<<< orphan*/  store_unsigned_integer (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  supply_register (int,unsigned char*) ; 

__attribute__((used)) static char *
rom68k_supply_one_register (int regno, unsigned char *hex)
{
  ULONGEST value;
  unsigned char regbuf[MAX_REGISTER_SIZE];

  value = 0;
  while (*hex != '\0')
    if (is_hex_digit (*hex))
      value = (value * 16) + hex_digit_value (*hex++);
    else
      break;

  /* Skip any whitespace.  */
  while (is_whitespace (*hex))
    hex++;

  store_unsigned_integer (regbuf, DEPRECATED_REGISTER_RAW_SIZE (regno), value);
  supply_register (regno, regbuf);

  return hex;
}