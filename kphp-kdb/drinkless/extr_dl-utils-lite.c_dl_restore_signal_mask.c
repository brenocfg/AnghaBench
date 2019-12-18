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
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  dl_assert (int,char*) ; 
 int /*<<< orphan*/  dl_passert (int,char*) ; 
 int /*<<< orphan*/  old_mask ; 
 scalar_t__ old_mask_inited ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dl_restore_signal_mask (void) {
  dl_assert (old_mask_inited != 0, "old_mask in not inited");
  int err = sigprocmask (SIG_SETMASK, &old_mask, NULL);
  dl_passert (err != -1, "failed to restore signal mask");
}