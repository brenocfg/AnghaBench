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
 scalar_t__* Buff ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* rptr ; 
 scalar_t__* wptr ; 
 int write (int,scalar_t__,int) ; 

void flushout (void) {
  int w, s;
  if (rptr[2] < wptr[2]) {
    s = wptr[2] - rptr[2];
    w = write (1, rptr[2], s);
    assert (w == s);
  }
  rptr[2] = wptr[2] = Buff[2];
}