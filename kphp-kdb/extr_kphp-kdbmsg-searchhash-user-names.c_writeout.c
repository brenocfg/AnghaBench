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
 int BUFFSIZE ; 
 int* Buff ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 
 int* wptr ; 

void writeout (const void *D, size_t len) {
  const char *d = D;
  while (len > 0) {
    int r = Buff[2] + BUFFSIZE - wptr[2];
    if (r > len) r = len;
    memcpy (wptr[2], d, r);
    d += r;
    wptr[2] += r;
    len -= r;
    if (len > 0) flushout();
  }                                
}