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
struct physical {scalar_t__ fd; TYPE_2__ link; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {int (* removefromset ) (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (struct physical*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
physical_RemoveFromSet(struct physical *p, fd_set *r, fd_set *w, fd_set *e)
{
  if (p->handler && p->handler->removefromset)
    return (*p->handler->removefromset)(p, r, w, e);
  else {
    int sets;

    sets = 0;
    if (p->fd >= 0) {
      if (r && FD_ISSET(p->fd, r)) {
        FD_CLR(p->fd, r);
        log_Printf(LogTIMER, "%s: fdunset(r) %d\n", p->link.name, p->fd);
        sets++;
      }
      if (e && FD_ISSET(p->fd, e)) {
        FD_CLR(p->fd, e);
        log_Printf(LogTIMER, "%s: fdunset(e) %d\n", p->link.name, p->fd);
        sets++;
      }
      if (w && FD_ISSET(p->fd, w)) {
        FD_CLR(p->fd, w);
        log_Printf(LogTIMER, "%s: fdunset(w) %d\n", p->link.name, p->fd);
        sets++;
      }
    }

    return sets;
  }
}