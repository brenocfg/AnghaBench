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
typedef  int apr_uint64_t ;

/* Variables and functions */

__attribute__((used)) static unsigned char *
write_packed_uint_body(unsigned char *buffer, apr_uint64_t value)
{
  while (value >= 0x80)
    {
      *(buffer++) = (unsigned char)((value % 0x80) + 0x80);
      value /= 0x80;
    }

  *(buffer++) = (unsigned char)value;
  return buffer;
}