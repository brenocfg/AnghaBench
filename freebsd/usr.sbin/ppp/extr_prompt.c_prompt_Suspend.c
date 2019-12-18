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
struct prompt {int dummy; } ;

/* Variables and functions */
 scalar_t__ getpgrp () ; 
 int /*<<< orphan*/  log_DeactivatePrompt (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TtyOldMode (struct prompt*) ; 
 scalar_t__ prompt_pgrp (struct prompt*) ; 

void
prompt_Suspend(struct prompt *p)
{
  if (getpgrp() == prompt_pgrp(p)) {
    prompt_TtyOldMode(p);
    log_DeactivatePrompt(p);
  }
}