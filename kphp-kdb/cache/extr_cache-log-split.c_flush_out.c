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
 int WB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  targ_fd ; 
 int /*<<< orphan*/  targ_fname ; 
 int true_wr_bytes ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int /*<<< orphan*/ ) ; 
 int wptr ; 
 int write (int /*<<< orphan*/ ,int,int) ; 
 int wst ; 

__attribute__((used)) static void flush_out (void) {
  int a, b = wptr - wst;
  assert (b >= 0);
  if (!b) {
    wptr = wst = WB;
    return;
  }
  a = write (targ_fd, wst, b);
  if (a > 0) {
    true_wr_bytes += a;
  }
  if (a < b) {
    kprintf ("error writing to %s: %d bytes written out of %d: %m\n", targ_fname, a, b);
    exit (3);
  }

  vkprintf  (1, "%d bytes written to %s\n", a, targ_fname);

  wptr = wst = WB;
}