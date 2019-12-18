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
struct physical {TYPE_1__ link; TYPE_2__* handler; } ;
struct execdevice {scalar_t__ fd_out; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int (* removefromset ) (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 struct execdevice* device2exec (TYPE_2__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int physical_RemoveFromSet (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
exec_RemoveFromSet(struct physical *p, fd_set *r, fd_set *w, fd_set *e)
{
  struct execdevice *dev = device2exec(p->handler);
  int sets;

  p->handler->removefromset = NULL;
  sets = physical_RemoveFromSet(p, r, w, e);
  p->handler->removefromset = exec_RemoveFromSet;

  if (dev->fd_out >= 0) {
    if (w && FD_ISSET(dev->fd_out, w)) {
      FD_CLR(dev->fd_out, w);
      log_Printf(LogTIMER, "%s: fdunset(w) %d\n", p->link.name, dev->fd_out);
      sets++;
    }
    if (e && FD_ISSET(dev->fd_out, e)) {
      FD_CLR(dev->fd_out, e);
      log_Printf(LogTIMER, "%s: fdunset(e) %d\n", p->link.name, dev->fd_out);
      sets++;
    }
  }

  return sets;
}