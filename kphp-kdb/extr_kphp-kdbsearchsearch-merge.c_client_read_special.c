#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gather_entry {int res_read; int res_bytes; int num; } ;
struct connection {int fd; int unread_res_bytes; scalar_t__ master_generation; TYPE_3__* gather; TYPE_1__* master; int /*<<< orphan*/  In; TYPE_2__* serv; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_queue; } ;
struct TYPE_7__ {int tot_num; int error_num; int wait_num; int ready_num; struct gather_entry* List; int /*<<< orphan*/  Alloc; } ;
struct TYPE_6__ {int id; } ;
struct TYPE_5__ {int fd; TYPE_4__* ev; } ;

/* Variables and functions */
 int CSN ; 
 int /*<<< orphan*/  advance_read_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int client_result_alloc (int /*<<< orphan*/ ,struct gather_entry*,char**) ; 
 int force_ready_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  free_unused_buffers (int /*<<< orphan*/ *) ; 
 char* get_read_ptr (int /*<<< orphan*/ *) ; 
 int get_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  put_event_into_heap (TYPE_4__*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static int client_read_special (struct connection *c) {
  int x = c->serv->id, t = 0, s, u;
  char *st, *to, *ptr;
  struct gather_entry *E;

  if (verbosity > 0) {
    fprintf (stderr, "in client_read_special for %d, %d unread bytes\n", c->fd, c->unread_res_bytes);
  }

  assert (x >= 0 && x < CSN);
  while (c->unread_res_bytes && (s = get_ready_bytes (&c->In)) > 0) {

    if (s > c->unread_res_bytes) {
      s = c->unread_res_bytes;
    }

    ptr = st = get_read_ptr (&c->In);
    if (c->gather && c->gather->tot_num > x) {
      E = &c->gather->List[x];

      if (verbosity > 1) {
        fprintf (stderr, "inside client_read_special for %d, %d unread bytes, %d bytes read, %d bytes total, %d bytes ready\n", c->fd, c->unread_res_bytes, E->res_read, E->res_bytes, s);
      }

      if (!E->res_read) {
        if (s < 4) {
          s = force_ready_bytes (&c->In, 16);
          if (s >= 4) {
            continue;
          }
          return 0;
        }
        E->num = *((int *) ptr);
        E->res_read = 4;
        if (E->num >= 0 && E->num <= 0x1000000) {
          ptr += 4;
          s -= 4;
          if (verbosity > 1) {
            fprintf (stderr, "got %d from %d\n", E->num, c->serv->id);
          }
        } else {
          E->num = -2;
          E->res_bytes += 4;
          c->gather->error_num++;
        }
      }

      while (s > 0 && (u = client_result_alloc (c->gather->Alloc, E, &to)) > 0) {
        if (verbosity > 1) {
          fprintf (stderr, "inside client_read_special for %d read loop: %d ready to read, %d in target chunk buffer at %p\n", c->fd, s, u, to);
        }
        if (u > s) { u = s; }
          memcpy (to, ptr, u);
        ptr += u;
        s -= u;
        E->res_read += u;
      }

      s = ptr - st;
    }

    if (verbosity > 1) {
      fprintf (stderr, "inside client_read_special for %d: advance read pointer by %d bytes\n", c->fd, s);
    }
    advance_read_ptr (&c->In, s);

    t += s;
    c->unread_res_bytes -= s;
    free_unused_buffers (&c->In);
  }

  if (!c->unread_res_bytes && c->gather && c->gather->tot_num >= x) {
    /* das ist alles */
    if (verbosity > 0) {
      fprintf (stderr, "socket %d completes reading data for master %d\n", c->fd, c->master->fd);
    }
    E = &c->gather->List[x];
    if (E->res_read != E->res_bytes) {
      fprintf (stderr, "res_read=%d res_bytes=%d unread=%d num=%d\n", E->res_read, E->res_bytes, c->unread_res_bytes, E->num);
      fprintf (stderr, "in connection %d gathering for master %d.%d, tot=%d err=%d ready=%d\n", c->fd, c->master->fd, x, c->gather->wait_num, c->gather->error_num, c->gather->ready_num);
    }
    assert (E->res_read == E->res_bytes);
    assert (++c->gather->ready_num <= c->gather->wait_num);
    if (c->gather->ready_num == c->gather->wait_num) {
      /* wake up master */
      if (verbosity > 0) {
  fprintf (stderr, "socket %d was the last one, waking master %d\n", c->fd, c->master->fd);
      }
      if (!c->master->ev->in_queue) {
  put_event_into_heap (c->master->ev);
      }
    }
    c->master = 0;
    c->gather = 0;
    c->master_generation = 0;
    //  c->state &= ~2;
  }

  return t;
}