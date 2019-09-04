#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int (* run ) (struct connection*) ;struct connection* type; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int ready; int state; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_NORD ; 
 int /*<<< orphan*/  C_NORW ; 
 int /*<<< orphan*/  C_NOWR ; 
 int EVT_FROM_EPOLL ; 
 int EVT_READ ; 
 int EVT_WRITE ; 
 int /*<<< orphan*/  assert (struct connection*) ; 
 int stub1 (struct connection*) ; 

int server_read_write_gateway (int fd, void *data, event_t *ev) {
  struct connection *c = (struct connection *) data;
  assert (c);
  assert (c->type);

  if (ev->ready & EVT_FROM_EPOLL) {
    // update C_NORD / C_NOWR only if we arrived from epoll()
    ev->ready &= ~EVT_FROM_EPOLL;
    c->flags &= ~C_NORW;
    if ((ev->state & EVT_READ) && !(ev->ready & EVT_READ)) {
      c->flags |= C_NORD;
    }
    if ((ev->state & EVT_WRITE) && !(ev->ready & EVT_WRITE)) {
      c->flags |= C_NOWR;
    }
  }

  return c->type->run (c);
}