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
struct physical {TYPE_1__ link; int /*<<< orphan*/  handler; } ;
struct fdescriptor {int dummy; } ;
struct execdevice {int fd_out; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 struct physical* descriptor2physical (struct fdescriptor*) ; 
 struct execdevice* device2exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int physical_doUpdateSet (struct fdescriptor*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_UpdateSet(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e, int *n)
{
  struct physical *p = descriptor2physical(d);
  struct execdevice *dev = device2exec(p->handler);
  int result = 0;

  if (w && dev->fd_out >= 0) {
    FD_SET(dev->fd_out, w);
    log_Printf(LogTIMER, "%s: fdset(w) %d\n", p->link.name, dev->fd_out);
    result++;
    w = NULL;
  }

  if (e && dev->fd_out >= 0) {
    FD_SET(dev->fd_out, e);
    log_Printf(LogTIMER, "%s: fdset(e) %d\n", p->link.name, dev->fd_out);
    result++;
  }

  if (result && *n <= dev->fd_out)
    *n = dev->fd_out + 1;

  return result + physical_doUpdateSet(d, r, w, e, n, 0);
}