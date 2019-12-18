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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int fromhex (char) ; 

void
decode_m_packet (char *from, CORE_ADDR *mem_addr_ptr, unsigned int *len_ptr)
{
  int i = 0, j = 0;
  char ch;
  *mem_addr_ptr = *len_ptr = 0;

  while ((ch = from[i++]) != ',')
    {
      *mem_addr_ptr = *mem_addr_ptr << 4;
      *mem_addr_ptr |= fromhex (ch) & 0x0f;
    }

  for (j = 0; j < 4; j++)
    {
      if ((ch = from[i++]) == 0)
	break;
      *len_ptr = *len_ptr << 4;
      *len_ptr |= fromhex (ch) & 0x0f;
    }
}