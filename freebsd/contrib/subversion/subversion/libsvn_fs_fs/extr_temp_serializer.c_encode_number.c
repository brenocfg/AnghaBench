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
typedef  int apr_int64_t ;

/* Variables and functions */

__attribute__((used)) static char*
encode_number(apr_int64_t number, char *key_buffer)
{
  /* encode the sign in the first byte */
  if (number < 0)
  {
    number = -number;
    *key_buffer = (char)((number & 63) + ' ' + 65);
  }
  else
    *key_buffer = (char)((number & 63) + ' ' + 1);
  number /= 64;

  /* write 7 bits / byte until no significant bits are left */
  while (number)
  {
    *++key_buffer = (char)((number & 127) + ' ' + 1);
    number /= 128;
  }

  /* return the last written position */
  return key_buffer;
}