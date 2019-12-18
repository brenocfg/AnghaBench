#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irep; } ;
struct RProc {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  codedump_recur (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_codedump_all(mrb_state *mrb, struct RProc *proc)
{
#ifndef MRB_DISABLE_STDIO
  codedump_recur(mrb, proc->body.irep);
#endif
}