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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  targ_fd ; 
 char* targ_fname ; 
 int true_wr_bytes ; 
 scalar_t__ verbosity ; 
 int wptr ; 
 int write (int /*<<< orphan*/ ,int,int) ; 
 int wst ; 

void flush_out (void) {
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
    fprintf (stderr, "error writing to %s: %d bytes written out of %d: %m\n", targ_fname, a, b);
    exit(3);
  }
  if (verbosity > 0) {
    fprintf (stderr, "%d bytes written to %s\n", a, targ_fname);
  }
  wptr = wst = WB;
}