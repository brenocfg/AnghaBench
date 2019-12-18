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
 long BUFFSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int idx_load_next (int) ; 
 int idx_rptr ; 
 int /*<<< orphan*/  writeout (int,int) ; 

void idx_copy_part (long len) {
  while (len > 0) {
    int to_load = len < BUFFSIZE ? len : BUFFSIZE;
    int bytes = idx_load_next (to_load);
    assert (bytes > 0);
    if (bytes > to_load) {
      assert (bytes <= to_load + 4);
      bytes = to_load;
    }
    writeout (idx_rptr, bytes);
    idx_rptr += bytes;
    len -= bytes;
  }
  assert (!len);
}