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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct physical {TYPE_2__* handler; TYPE_1__ link; } ;
struct ngdevice {scalar_t__ cs; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int (* removefromset ) (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 struct ngdevice* device2ng (TYPE_2__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ physical_RemoveFromSet (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_RemoveFromSet(struct physical *p, fd_set *r, fd_set *w, fd_set *e)
{
  struct ngdevice *dev = device2ng(p->handler);
  int result;

  if (r && dev->cs >= 0 && FD_ISSET(dev->cs, r)) {
    FD_CLR(dev->cs, r);
    log_Printf(LogTIMER, "%s: fdunset(ctrl) %d\n", p->link.name, dev->cs);
    result = 1;
  } else
    result = 0;

  /* Careful... physical_RemoveFromSet() called us ! */

  p->handler->removefromset = NULL;
  result += physical_RemoveFromSet(p, r, w, e);
  p->handler->removefromset = ng_RemoveFromSet;

  return result;
}