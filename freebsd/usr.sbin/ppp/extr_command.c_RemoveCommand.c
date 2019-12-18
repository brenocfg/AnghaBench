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
struct cmdargs {scalar_t__ argc; scalar_t__ argn; TYPE_1__* cx; int /*<<< orphan*/  bundle; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DATALINK_CLOSED ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  bundle_DatalinkRemove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
RemoveCommand(struct cmdargs const *arg)
{
  if (arg->argc != arg->argn)
    return -1;

  if (arg->cx->state != DATALINK_CLOSED) {
    log_Printf(LogWARN, "remove: Cannot delete links that aren't closed\n");
    return 2;
  }

  bundle_DatalinkRemove(arg->bundle, arg->cx);
  return 0;
}