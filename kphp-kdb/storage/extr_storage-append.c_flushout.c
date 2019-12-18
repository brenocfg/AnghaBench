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
 scalar_t__ Buff ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ rptr ; 
 int /*<<< orphan*/  wfd ; 
 scalar_t__ wptr ; 
 int write (int /*<<< orphan*/ ,scalar_t__,int) ; 

int flushout (void) {
  int w, s;
  while (rptr < wptr) {
    s = wptr - rptr;
    w = write (wfd, rptr, s);
    if (w != s) {
      kprintf ("write (%d, %p, %d) fail, written %d bytes, %m\n", wfd, rptr, s, w);
      if (w > 0 && w < s) {
        rptr += w;
        continue;
      }
      return -1;
    } else {
      break;
    }
  }
  rptr = wptr = Buff;
  return 0;
}