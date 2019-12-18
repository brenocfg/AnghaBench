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

/* Variables and functions */
 unsigned int CRC16 ; 
 unsigned int* crctab ; 
 unsigned int* xmalloc (int) ; 

__attribute__((used)) static void
crcinit (void)
{
  static int crctab_inited = 0;
  int val;

  if (crctab_inited == 1)
    return;

  crctab = xmalloc (256 * sizeof (short));

  for (val = 0; val <= 255; val++)
    {
      int i;
      unsigned int crc;

      crc = val << 8;

      for (i = 0; i < 8; ++i)
	{
	  crc <<= 1;

	  if (crc & 0x10000)
	    crc ^= CRC16;
	}

      crctab[val] = crc;
    }

  crctab_inited = 1;
}