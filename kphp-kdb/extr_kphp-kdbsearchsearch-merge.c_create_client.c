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
struct connection {int fd; int /*<<< orphan*/  state; struct connection* prev; struct connection* next; int /*<<< orphan*/  out_buff; int /*<<< orphan*/  Out; int /*<<< orphan*/  in_buff; int /*<<< orphan*/  In; struct cluster_server* serv; int /*<<< orphan*/ * ev; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct cluster_server {int port; int id; TYPE_1__ addr; int /*<<< orphan*/  conn; struct connection* c; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_SIZE ; 
 int /*<<< orphan*/  C_INCONN ; 
 struct connection* Connections ; 
 int EVT_SPEC ; 
 int EVT_WRITE ; 
 int /*<<< orphan*/ * Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int client_socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_worker ; 
 int /*<<< orphan*/  epoll_insert (int,int) ; 
 int /*<<< orphan*/  epoll_sethandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  init_builtin_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outbound_connections ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

struct connection *create_client (struct cluster_server *S) {
  int cfd = client_socket (S->addr.s_addr, S->port, 0);
  struct connection *c, *h;
  event_t *ev;

  if (cfd < 0) {
    fprintf (stderr, "error connecting to %s:%d: %m", inet_ntoa(S->addr), S->port);
    exit(1);
  }

  assert (cfd < MAX_EVENTS);

  ev = Events + cfd;
  //  memcpy (&ev->peer, &peer, sizeof(peer));

  c = Connections + cfd;
  memset (c, 0, sizeof (struct connection));
  c->fd = cfd;
  c->ev = ev;
  c->serv = S;

  init_builtin_buffer (&c->In, c->in_buff, BUFF_SIZE);
  init_builtin_buffer (&c->Out, c->out_buff, BUFF_SIZE);

  epoll_sethandler (cfd, 0, client_worker, c);
  epoll_insert (cfd, EVT_WRITE | EVT_SPEC);
  if (verbosity > 1) {
    fprintf (stderr, "after insert()\n");
  }

  if (!S->c) {
    c->next = c->prev = S->c = c;
  } else {
    h = S->c;
    c->next = h;
    c->prev = h->prev;
    h->prev->next = c;
    h->prev = c;
  }

  c->state = C_INCONN;  /* connecting */
  S->conn++;
  outbound_connections++;

  if (verbosity > 0) {
    fprintf (stderr, "outbound connection #%d: handle %d to %s:%d\n", S->id, c->fd, inet_ntoa(S->addr), S->port);
  }

  return c;
}