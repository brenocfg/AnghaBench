#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct prompt {int nonewline; int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {char* name; struct prompt* arg; int /*<<< orphan*/  load; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECTICKS ; 
 TYPE_1__ bgtimer ; 
 scalar_t__ getpgrp () ; 
 int /*<<< orphan*/  log_ActivatePrompt (struct prompt*) ; 
 int /*<<< orphan*/  prompt_Required (struct prompt*) ; 
 int /*<<< orphan*/  prompt_TimedContinue ; 
 int /*<<< orphan*/  prompt_TtyCommandMode (struct prompt*) ; 
 scalar_t__ prompt_pgrp (struct prompt*) ; 
 int /*<<< orphan*/  timer_Start (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_1__*) ; 

void
prompt_Continue(struct prompt *p)
{
  timer_Stop(&bgtimer);
  if (getpgrp() == prompt_pgrp(p)) {
    prompt_TtyCommandMode(p);
    p->nonewline = 1;
    prompt_Required(p);
    log_ActivatePrompt(p);
  } else if (!p->owner) {
    bgtimer.func = prompt_TimedContinue;
    bgtimer.name = "prompt bg";
    bgtimer.load = SECTICKS;
    bgtimer.arg = p;
    timer_Start(&bgtimer);
  }
}