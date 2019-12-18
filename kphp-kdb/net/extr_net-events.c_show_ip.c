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
 scalar_t__ sprintf (char*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

char *show_ip (unsigned ip) {
  static char abuf[256], *ptr = abuf;
  char *res;
  if (ptr > abuf + 200) {
    ptr = abuf;
  }
  res = ptr;
  ptr += sprintf (ptr, "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff) + 1;
  return res;
}