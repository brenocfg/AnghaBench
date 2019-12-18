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
typedef  int unw_word ;

/* Variables and functions */

__attribute__((used)) static unw_word
unw_decode_uleb128 (unsigned char **dpp)
{
  unsigned shift = 0;
  unw_word byte, result = 0;
  unsigned char *bp = *dpp;

  while (1)
    {
      byte = *bp++;
      result |= (byte & 0x7f) << shift;
      if ((byte & 0x80) == 0)
	break;
      shift += 7;
    }
  *dpp = bp;
  return result;
}