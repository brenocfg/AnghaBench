#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int fd; int /*<<< orphan*/  out_buff; int /*<<< orphan*/  Out; int /*<<< orphan*/  in_buff; int /*<<< orphan*/  In; TYPE_2__* ev; } ;
struct sockaddr {int dummy; } ;
struct connection {int fd; int /*<<< orphan*/  out_buff; int /*<<< orphan*/  Out; int /*<<< orphan*/  in_buff; int /*<<< orphan*/  In; TYPE_2__* ev; } ;
typedef  int /*<<< orphan*/  peer ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int sin_port; TYPE_1__ sin_addr; } ;
struct TYPE_7__ {TYPE_3__ peer; } ;
typedef  TYPE_2__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_SIZE ; 
 struct sockaddr_in* Connections ; 
 int EVA_CONTINUE ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 TYPE_2__* Events ; 
 int MAX_CONNECTIONS ; 
 int MAX_EVENTS ; 
 int accept (int,struct sockaddr*,unsigned int*) ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* conv_addr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  epoll_insert (int,int) ; 
 int /*<<< orphan*/  epoll_sethandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_builtin_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_read_write ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int accept_new_connections (int fd, void *data, event_t *ev) {
  char buf[32];
  struct sockaddr_in peer;
  unsigned addrlen;
  int cfd, acc = 0;
  struct connection *c;
  do {
    addrlen = sizeof(peer);
    memset (&peer, 0, sizeof(peer));
    cfd = accept (fd, (struct sockaddr *) &peer, &addrlen);
    if (cfd < 0) {
      if (!acc && verbosity > 0) {
	fprintf (stderr, "accept(%d) unexpectedly returns %d\n", fd, cfd);
      }
      break;
    } else acc++;
    assert (cfd < MAX_EVENTS);
    ev = Events + cfd;
    memcpy (&ev->peer, &peer, sizeof(peer));
    if (verbosity > 0) {
      fprintf (stderr, "accepted incoming connection at %s:%d, fd=%d\n", conv_addr(ev->peer.sin_addr.s_addr, buf), ev->peer.sin_port, cfd);
    }
    if (cfd >= MAX_CONNECTIONS) {
      close (cfd);
      continue;
    }
    c = Connections + cfd;
    memset (c, 0, sizeof (struct connection));
    c->fd = cfd;
    c->ev = ev;
    init_builtin_buffer (&c->In, c->in_buff, BUFF_SIZE);
    init_builtin_buffer (&c->Out, c->out_buff, BUFF_SIZE);
    epoll_sethandler (cfd, 0, server_read_write, c);
    epoll_insert (cfd, EVT_READ | EVT_SPEC);
    active_connections++;
  } while (1);
  return EVA_CONTINUE;
}