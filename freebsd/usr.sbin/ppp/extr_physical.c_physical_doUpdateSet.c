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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct physical {int fd; TYPE_1__ link; scalar_t__ out; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 struct physical* descriptor2physical (struct fdescriptor*) ; 
 scalar_t__ link_QueueLen (TYPE_1__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int
physical_doUpdateSet(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e,
                     int *n, int force)
{
  struct physical *p = descriptor2physical(d);
  int sets;

  sets = 0;
  if (p->fd >= 0) {
    if (r) {
      FD_SET(p->fd, r);
      log_Printf(LogTIMER, "%s: fdset(r) %d\n", p->link.name, p->fd);
      sets++;
    }
    if (e) {
      FD_SET(p->fd, e);
      log_Printf(LogTIMER, "%s: fdset(e) %d\n", p->link.name, p->fd);
      sets++;
    }
    if (w && (force || link_QueueLen(&p->link) || p->out)) {
      FD_SET(p->fd, w);
      log_Printf(LogTIMER, "%s: fdset(w) %d\n", p->link.name, p->fd);
      sets++;
    }
    if (sets && *n < p->fd + 1)
      *n = p->fd + 1;
  }

  return sets;
}