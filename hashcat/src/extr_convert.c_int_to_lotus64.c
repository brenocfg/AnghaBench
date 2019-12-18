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

/* Variables and functions */

u8 int_to_lotus64 (const u8 c)
{
  if (c  < 10) return '0' + c;
  if (c  < 36) return 'A' + c - 10;
  if (c  < 62) return 'a' + c - 36;
  if (c == 62) return '+';
  if (c == 63) return '/';

  return 0;
}