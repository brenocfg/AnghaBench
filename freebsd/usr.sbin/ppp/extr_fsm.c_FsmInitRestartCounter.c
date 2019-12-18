#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* arg; int /*<<< orphan*/  func; } ;
struct fsm {TYPE_1__* fn; TYPE_2__ FsmTimer; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* InitRestartCounter ) (struct fsm*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FsmTimeout ; 
 int /*<<< orphan*/  stub1 (struct fsm*,int) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_2__*) ; 

__attribute__((used)) static void
FsmInitRestartCounter(struct fsm *fp, int what)
{
  timer_Stop(&fp->FsmTimer);
  fp->FsmTimer.func = FsmTimeout;
  fp->FsmTimer.arg = (void *)fp;
  (*fp->fn->InitRestartCounter)(fp, what);
}