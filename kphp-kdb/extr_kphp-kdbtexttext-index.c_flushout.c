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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fd ; 
 scalar_t__ rptr ; 
 scalar_t__ wptr ; 
 int write (int /*<<< orphan*/ ,scalar_t__,int) ; 

void flushout (void) {
  int w, s;
  if (rptr < wptr) {
    s = wptr - rptr;
    w = write (fd[0], rptr, s);
    assert (w == s);
  }
  rptr = wptr = Buff;
}