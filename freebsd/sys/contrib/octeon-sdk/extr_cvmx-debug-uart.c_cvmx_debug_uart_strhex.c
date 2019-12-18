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

__attribute__((used)) static void cvmx_debug_uart_strhex(char *str, unsigned char t)
{
  char hexchar[] = "0123456789ABCDEF";
  str[0] = hexchar[(t>>4)];
  str[1] = hexchar[t&0xF];
  str[2] = 0;
}