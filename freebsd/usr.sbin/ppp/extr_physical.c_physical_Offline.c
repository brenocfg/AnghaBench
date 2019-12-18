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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct physical {TYPE_2__ link; TYPE_1__* handler; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* offline ) (struct physical*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct physical*) ; 

void
physical_Offline(struct physical *p)
{
  if (p->handler && p->handler->offline)
    (*p->handler->offline)(p);
  log_Printf(LogPHASE, "%s: Disconnected!\n", p->link.name);
}