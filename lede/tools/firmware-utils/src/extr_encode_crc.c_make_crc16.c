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
 int POLYNOM ; 

int make_crc16(int crc, char new)
{
  int i;
  crc = crc ^ (((int)new) << 8);
  
  for(i=0; i<8; i++) {  // work on 8 bits in "new"
    crc <<= 1;          // MSBs first
    if(crc & 0x10000)  crc ^= POLYNOM;
  }
  return crc & 0xFFFF;
}