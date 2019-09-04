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
 int hex_convert (int const) ; 

u8 hex_to_u8 (const u8 hex[2])
{
  u8 v = 0;

  v |= (hex_convert (hex[1]) << 0);
  v |= (hex_convert (hex[0]) << 4);

  return (v);
}