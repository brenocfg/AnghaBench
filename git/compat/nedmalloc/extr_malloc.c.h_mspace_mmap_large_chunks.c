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
typedef  int /*<<< orphan*/  mstate ;
typedef  int /*<<< orphan*/  mspace ;

/* Variables and functions */
 int /*<<< orphan*/  POSTACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREACTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_mmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_mmap (int /*<<< orphan*/ ) ; 
 scalar_t__ use_mmap (int /*<<< orphan*/ ) ; 

int mspace_mmap_large_chunks(mspace msp, int enable) {
  int ret = 0;
  mstate ms = (mstate)msp;
  if (!PREACTION(ms)) {
    if (use_mmap(ms))
      ret = 1;
    if (enable)
      enable_mmap(ms);
    else
      disable_mmap(ms);
    POSTACTION(ms);
  }
  return ret;
}