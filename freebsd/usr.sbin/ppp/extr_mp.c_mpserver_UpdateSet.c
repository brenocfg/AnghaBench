#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* dl; } ;
struct mpserver {int fd; TYPE_2__ send; int /*<<< orphan*/  socket; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {TYPE_1__* physical; } ;
struct TYPE_5__ {int /*<<< orphan*/  out; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 int /*<<< orphan*/  bundle_SendDatalink (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ datalink_RemoveFromSet (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mpserver* descriptor2mpserver (struct fdescriptor*) ; 
 int /*<<< orphan*/  link_QueueLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
mpserver_UpdateSet(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e,
                   int *n)
{
  struct mpserver *s = descriptor2mpserver(d);
  int result;

  result = 0;
  if (s->send.dl != NULL) {
    /* We've connect()ed */
    if (!link_QueueLen(&s->send.dl->physical->link) &&
        !s->send.dl->physical->out) {
      /* Only send if we've transmitted all our data (i.e. the ConfigAck) */
      result -= datalink_RemoveFromSet(s->send.dl, r, w, e);
      bundle_SendDatalink(s->send.dl, s->fd, &s->socket);
      s->send.dl = NULL;
      s->fd = -1;
    } else
      /* Never read from a datalink that's on death row ! */
      result -= datalink_RemoveFromSet(s->send.dl, r, NULL, NULL);
  } else if (r && s->fd >= 0) {
    if (*n < s->fd + 1)
      *n = s->fd + 1;
    FD_SET(s->fd, r);
    log_Printf(LogTIMER, "mp: fdset(r) %d\n", s->fd);
    result++;
  }
  return result;
}