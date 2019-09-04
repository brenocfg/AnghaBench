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
struct connection {int state; int fd; int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int C_NOWR ; 
 int C_WANTWR ; 
 int EVT_WRITE ; 
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  advance_read_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int /*<<< orphan*/  free_unused_buffers (int /*<<< orphan*/ *) ; 
 char* get_read_ptr (int /*<<< orphan*/ *) ; 
 int get_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int send (int,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int server_writer (struct connection *c) {
  int r, s, t = 0;
  char *to;

  while ((c->state & C_WANTWR) != 0) {
    // write buffer loop
    s = get_ready_bytes (&c->Out);

    if (!s) {
      c->state &= ~C_WANTWR;
      break;
    }

    if (c->state & C_NOWR) {
      break;
    }

    to = get_read_ptr (&c->Out);

    r = send (c->fd, to, s, MSG_DONTWAIT | MSG_NOSIGNAL);

    if (verbosity > 0) {
      fprintf (stderr, "send() to %d: %d written out of %d at %p\n", c->fd, r, s, to);
      if (r < 0) perror ("send()");
    }

    if (r > 0) {
      advance_read_ptr (&c->Out, r);
      t += r;
    }

    if (r < s) {
      c->state |= C_NOWR;
    }

  }

  if (t) {
    free_unused_buffers (&c->Out);
  }

  return c->state & C_WANTWR ? EVT_WRITE : 0;
}