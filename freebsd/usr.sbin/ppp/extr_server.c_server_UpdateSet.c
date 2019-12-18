#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct server {int fd; } ;
struct prompt {int /*<<< orphan*/  desc; struct prompt* next; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogTIMER ; 
 struct server* descriptor2server (struct fdescriptor*) ; 
 scalar_t__ descriptor_UpdateSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 
 struct prompt* log_PromptList () ; 

__attribute__((used)) static int
server_UpdateSet(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e, int *n)
{
  struct server *s = descriptor2server(d);
  struct prompt *p;
  int sets;

  sets = 0;
  if (r && s->fd >= 0) {
    if (*n < s->fd + 1)
      *n = s->fd + 1;
    FD_SET(s->fd, r);
    log_Printf(LogTIMER, "server: fdset(r) %d\n", s->fd);
    sets++;
  }

  for (p = log_PromptList(); p; p = p->next)
    sets += descriptor_UpdateSet(&p->desc, r, w, e, n);

  return sets;
}