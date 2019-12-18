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
 int /*<<< orphan*/  SWS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kfs_sws_write (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int metafile_pos ; 
 int newidx_fd ; 
 scalar_t__ rptr ; 
 scalar_t__ wptr ; 
 scalar_t__ wptr0 ; 
 int write (int,scalar_t__,int) ; 
 int write_pos ; 

void flushout (void) {
  int s;
  if (wptr > wptr0) {
    s = wptr - wptr0;
    write_pos += s;
    metafile_pos += s;
  }
  if (rptr < wptr) {
    s = wptr - rptr;
    if (newidx_fd >= 1) {
      assert (write (newidx_fd, rptr, s) == s);
    } else {
      kfs_sws_write (&SWS, rptr, s);
    }
  }
  rptr = wptr = wptr0 = Buff;
}