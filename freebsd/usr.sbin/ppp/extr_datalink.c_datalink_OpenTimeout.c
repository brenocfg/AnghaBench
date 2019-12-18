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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct datalink {scalar_t__ state; int /*<<< orphan*/  name; TYPE_1__ dial; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPENING ; 
 int /*<<< orphan*/  LogCHAT ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
datalink_OpenTimeout(void *v)
{
  struct datalink *dl = (struct datalink *)v;

  timer_Stop(&dl->dial.timer);
  if (dl->state == DATALINK_OPENING)
    log_Printf(LogCHAT, "%s: Redial timer expired.\n", dl->name);
}