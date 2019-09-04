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
struct connection {int fd; int error; int state; int /*<<< orphan*/  In; scalar_t__ unread_res_bytes; } ;

/* Variables and functions */
 int C_NORD ; 
 int C_WANTRD ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  advance_read_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int client_execute (struct connection*,char*,int) ; 
 int client_read_special (struct connection*) ; 
 scalar_t__ errno ; 
 int force_ready_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free_all_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_unused_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_client_gather (struct connection*) ; 
 char* get_read_ptr (int /*<<< orphan*/ *) ; 
 int get_ready_bytes (int /*<<< orphan*/ *) ; 
 char* get_write_ptr (int /*<<< orphan*/ *,int) ; 
 int get_write_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int client_reader (struct connection *c) {

  char *st, *ptr, *to;
  int r, s, t = 0;

  if (verbosity > 1) {
    fprintf (stderr, "in client_reader(%d)\n", c->fd);
  }

  if (c->unread_res_bytes) {
    get_client_gather (c);
    t = client_read_special (c);
  }

  to = get_write_ptr (&c->In, 512);
  s = get_write_space (&c->In);

  if (s <= 0) {
    free_all_buffers(&c->In);
    c->error = 8;
    to = get_write_ptr (&c->In, 512);
    s = get_write_space (&c->In);
  }

  assert (to && s > 0);

  if (!(c->state & C_NORD)) {
    r = recv (c->fd, to, s, MSG_DONTWAIT);

    if (verbosity > 0) {
      fprintf (stderr, "recv() from %d: %d read out of %d at %p\n", c->fd, r, s, to);
      if (r < 0 && errno != EAGAIN) perror ("recv()");
    }

  } else {
    r = 0;
  }

  if (r < s) {
    c->state |= C_NORD;
  }

  if (r > 0) {
    advance_write_ptr (&c->In, r);
  } else if (c->unread_res_bytes) {
    c->state |= C_WANTRD;
    return 2;
  }

  if (c->unread_res_bytes) {
    get_client_gather (c);
    client_read_special (c);
    return 0;
  }

  do {
    ptr = st = get_read_ptr (&c->In);
    s = get_ready_bytes (&c->In);
    if (!s) { return 0; }
    to = st + (s > 1024 ? 1024 : s);

    while (ptr < to && *ptr != 10) {
      ptr++;
    }

    if (ptr >= to) {
      if (to - st >= 1024) {
  if (verbosity > 0) {
    fprintf (stderr, "client socket #%d: command line longer than 1024 bytes\n", c->fd);
  }
  advance_read_ptr (&c->In, to - st);
  return -1;
      } else {
  r = force_ready_bytes (&c->In, 1024);
  return r <= s ? -1 : 0;
      }
    }

    to = ptr;
    s = to - st + 1;
    *to = 0;
    if (to > st && to[-1] == '\r') {
      *--to = 0;
    }

    r = client_execute (c, st, to - st);

    advance_read_ptr (&c->In, s);

    if (r < 0) {
      return -1;
    }

    free_unused_buffers (&c->In);
  } while (!r);

  return r;
}