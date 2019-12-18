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
typedef  unsigned char cyg_uint32 ;

/* Variables and functions */
 unsigned char* crc32_tab ; 

cyg_uint32 
cyg_crc32_accumulate(cyg_uint32 crc32val, unsigned char *s, int len)
{
  int i;

  for (i = 0;  i < len;  i++) {
    crc32val = crc32_tab[(crc32val ^ s[i]) & 0xff] ^ (crc32val >> 8);
  }
  return crc32val;
}