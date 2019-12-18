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
struct server {scalar_t__ fd; } ;
struct prompt {int /*<<< orphan*/  desc; struct prompt* next; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 struct server* descriptor2server (struct fdescriptor*) ; 
 scalar_t__ descriptor_IsSet (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct prompt* log_PromptList () ; 

__attribute__((used)) static int
server_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct server *s = descriptor2server(d);
  struct prompt *p;

  if (s->fd >= 0 && FD_ISSET(s->fd, fdset))
    return 1;

  for (p = log_PromptList(); p; p = p->next)
    if (descriptor_IsSet(&p->desc, fdset))
      return 1;

  return 0;
}