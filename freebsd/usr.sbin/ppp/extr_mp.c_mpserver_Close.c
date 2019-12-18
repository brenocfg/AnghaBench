#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dl; } ;
struct mpserver {int fd; TYPE_2__ socket; TYPE_1__ send; } ;

/* Variables and functions */
 int ID0unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  bundle_SendDatalink (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
mpserver_Close(struct mpserver *s)
{
  if (s->send.dl != NULL) {
    bundle_SendDatalink(s->send.dl, s->fd, &s->socket);
    s->send.dl = NULL;
    s->fd = -1;
  } else if (s->fd >= 0) {
    close(s->fd);
    if (ID0unlink(s->socket.sun_path) == -1)
      log_Printf(LogERROR, "%s: Failed to remove: %s\n", s->socket.sun_path,
                strerror(errno));
    memset(&s->socket, '\0', sizeof s->socket);
    s->fd = -1;
  }
}