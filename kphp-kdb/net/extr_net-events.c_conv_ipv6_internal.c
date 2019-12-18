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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohs (unsigned short const) ; 
 int sprintf (char*,char*,unsigned short const,...) ; 

int conv_ipv6_internal (const unsigned short a[8], char *buf) {
  int i, j = 0, k = 0, l = 0;
  for (i = 0; i < 8; i++) {
    if (a[i]) {
      if (j > l) {
	l = j;
	k = i;
      }
      j = 0;
    } else {
      j++;
    }
  }
  if (j == 8) {
    memcpy (buf, "::", 3);
    return 2;
  }
  if (l == 5 && a[5] == 0xffff) {
    return sprintf (buf, "::ffff:%d.%d.%d.%d", a[6]&255, a[6]>>8, a[7]&255, a[7]>>8);
  }
  char *ptr = buf;
  if (l) {
    for (i = 0; i < k - l; i++) {
      ptr += sprintf (ptr, "%x:", ntohs (a[i]));
    }
    if (!i || k == 8) {
      *ptr++ = ':';
    }
    for (i = k; i < 8; i++) {
      ptr += sprintf (ptr, ":%x", ntohs (a[i]));
    } 
  } else {
    for (i = 0; i < 7; i++) {
      ptr += sprintf (ptr, "%x:", ntohs (a[i]));
    }
    ptr += sprintf (ptr, "%x", ntohs (a[i]));
  }
  return ptr - buf;
}