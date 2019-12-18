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
 unsigned short* crctab ; 

__attribute__((used)) static unsigned short
docrc (unsigned char *p, int len)
{
  unsigned short crc = 0;

  while (len-- > 0)
    crc = (crc << 8) ^ crctab[(crc >> 8) ^ *p++];

  return crc;
}