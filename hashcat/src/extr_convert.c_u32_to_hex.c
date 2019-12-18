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
typedef  char u8 ;
typedef  int u32 ;

/* Variables and functions */

void u32_to_hex (const u32 v, u8 hex[8])
{
  const u8 tbl[0x10] =
  {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f',
  };

  hex[1] = tbl[v >>  0 & 15];
  hex[0] = tbl[v >>  4 & 15];
  hex[3] = tbl[v >>  8 & 15];
  hex[2] = tbl[v >> 12 & 15];
  hex[5] = tbl[v >> 16 & 15];
  hex[4] = tbl[v >> 20 & 15];
  hex[7] = tbl[v >> 24 & 15];
  hex[6] = tbl[v >> 28 & 15];
}