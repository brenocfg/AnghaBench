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
struct connection {int fd; scalar_t__ state; int /*<<< orphan*/  Out; TYPE_1__* ev; } ;
struct TYPE_2__ {int state; int ready; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 int EVT_WRITE ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  advance_read_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 char* get_read_ptr (int /*<<< orphan*/ *) ; 
 int get_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int server_writer (struct connection *c) {
  int r, s, fd = c->fd;
  event_t *ev = c->ev;

  if (c->state > 0) {
    // write buffer loop
    s = get_ready_bytes (&c->Out);

    while ((s = get_ready_bytes (&c->Out)) && (!(ev->state & EVT_WRITE) || (ev->ready & EVT_WRITE))) {
      char *to = get_read_ptr (&c->Out);

      r = send (fd, to, s, MSG_DONTWAIT);

      if (verbosity > 0) {
	fprintf (stderr, "send() to %d: %d written out of %d at %p\n", fd, r, s, to);
	if (r < 0) perror ("send()");
      }

      if (r > 0) {
	advance_read_ptr (&c->Out, r);
      }

      if (r < s) {
	ev->ready &= ~EVT_WRITE;
	break;
      }
    }

    if (s > 0) return EVT_WRITE;
      
    c->state = 0;
  }
  return 0;
}