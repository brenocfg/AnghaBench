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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int* crctab32 ; 

__attribute__((used)) static u32 partial_crc32_one(u8 c, u32 crc)
{
	return crctab32[(crc ^ c) & 0xff] ^ (crc >> 8);
}