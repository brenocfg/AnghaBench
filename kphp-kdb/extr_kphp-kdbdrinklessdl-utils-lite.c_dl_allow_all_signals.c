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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  dl_passert (int,char*) ; 
 int /*<<< orphan*/  old_mask ; 
 int old_mask_inited ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dl_allow_all_signals (void) {
  sigset_t mask;
  sigemptyset (&mask);
  int err = sigprocmask (SIG_SETMASK, &mask, &old_mask);
  old_mask_inited = 1;
  dl_passert (err != -1, "failed to allow all signals");
}