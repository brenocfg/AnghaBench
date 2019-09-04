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
struct connection {int state; scalar_t__ error; int /*<<< orphan*/  Out; int /*<<< orphan*/  In; TYPE_1__* gather; scalar_t__ Tmp; } ;
struct TYPE_5__ {int epoll_ready; int state; int ready; scalar_t__ data; } ;
typedef  TYPE_2__ event_t ;
struct TYPE_4__ {scalar_t__ timeout_time; scalar_t__ ready_num; scalar_t__ wait_num; } ;

/* Variables and functions */
 int C_INQUERY ; 
 int C_NORD ; 
 int C_NORW ; 
 int C_NOWR ; 
 int C_WANTRD ; 
 int C_WANTWR ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLRDHUP ; 
 int EVA_DESTROY ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 int EVT_WRITE ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  assert (struct connection*) ; 
 int end_search_query (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free_all_buffers (scalar_t__) ; 
 int /*<<< orphan*/  free_connection_buffers (struct connection*) ; 
 int /*<<< orphan*/  free_unused_buffers (int /*<<< orphan*/ *) ; 
 scalar_t__ get_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct connection*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ now ; 
 int server_reader (struct connection*) ; 
 int server_writer (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int server_read_write (int fd, void *data, event_t *ev) {
  struct connection *c = (struct connection *) data;
  int res;
  assert (c);

  if (ev->epoll_ready & (EPOLLHUP | EPOLLERR | EPOLLRDHUP)) {
    if (verbosity > 0) {
      fprintf (stderr, "socket %d: disconnected, cleaning\n", fd);
    }
    free_connection_buffers (c);
    memset (c, 0, sizeof(struct connection));
    ev->data = 0;
    active_connections--;
    // close (fd);
    return EVA_DESTROY;
  }

  c->state &= ~C_NORW;
  if ((ev->state & EVT_READ) && !(ev->ready & EVT_READ)) { c->state |= C_NORD; }
  if ((ev->state & EVT_WRITE) && !(ev->ready & EVT_WRITE)) { c->state |= C_NOWR; }

  if (c->gather && (now >= c->gather->timeout_time || c->gather->ready_num == c->gather->wait_num)) {
    res = end_search_query (c);
    free_all_buffers (c->Tmp);
    c->Tmp = 0;
  }

  while ((((c->state & (C_WANTRD | C_INQUERY)) == C_WANTRD) && !(c->state & C_NORD)) || ((c->state & C_WANTWR) && !(c->state & C_NOWR))) {

    res = server_writer (c);
    if (res) { break; }

    if (!c->gather && !(c->state & C_INQUERY)) {
      res = server_reader (c);
      if (verbosity) {
  fprintf (stderr, "server_reader=%d, ready=%02x, state=%02x\n", res, ev->ready, ev->state);
      }
      if (res > 0) { break; }
    }

    if (get_ready_bytes(&c->Out)) {
      c->state |= C_WANTWR;
    }
  }

  free_unused_buffers(&c->In);
  free_unused_buffers(&c->Out);

  if (c->error < 0) {
    if (verbosity > 0) {
      fprintf (stderr, "socket %d: closing and cleaning (error code=%d)\n", fd, c->error);
    }
    free_connection_buffers (c);
    memset (c, 0, sizeof(struct connection));
    ev->data = 0;
    active_connections--;
    // close (fd);
    return EVA_DESTROY;
  }

  return (c->state & C_WANTRD ? EVT_READ : 0) | (c->state & C_WANTWR ? EVT_WRITE : 0) | EVT_SPEC;
}