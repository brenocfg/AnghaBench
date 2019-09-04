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
 int /*<<< orphan*/  USAGE_ERROR_ACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ok_magic (int /*<<< orphan*/ ) ; 
 int sys_trim (int /*<<< orphan*/ ,size_t) ; 

int mspace_trim(mspace msp, size_t pad) {
  int result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    if (!PREACTION(ms)) {
      result = sys_trim(ms, pad);
      POSTACTION(ms);
    }
  }
  else {
    USAGE_ERROR_ACTION(ms,ms);
  }
  return result;
}