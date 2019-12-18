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
 scalar_t__ Buff ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  newidx_fd ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 scalar_t__ verbosity ; 
 scalar_t__ wptr ; 
 int write (int /*<<< orphan*/ ,scalar_t__,int) ; 

void flushout (void) {
  if (Buff < wptr) {
    int s = wptr - Buff;
    int w = write (newidx_fd, Buff, s);
    int e = errno;
    if (verbosity) {
      fprintf (stderr, "(s,w,BUFFSIZE) = (%d %d %d)\n", s, w, BUFFSIZE);
    }
    if (w == -1) {
      fprintf (stderr, "errno = %d (%s)\n", e, strerror (e));
    }
    assert (w == s);
  }
  wptr = Buff;
}