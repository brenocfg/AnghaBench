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
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

char *conv_addr (in_addr_t a, char *buf) {
  static char abuf[64];
  if (!buf) {
    buf = abuf;
  }
  sprintf (buf, "%d.%d.%d.%d", a&255, (a>>8)&255, (a>>16)&255, a>>24);
  return buf;
}