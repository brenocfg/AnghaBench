#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gather_data {scalar_t__ timeout_time; TYPE_3__* c; struct gather_data* next; } ;
struct TYPE_7__ {int fd; TYPE_1__* ev; } ;
struct TYPE_6__ {scalar_t__ reconnect_time; int /*<<< orphan*/  conn_retries; int /*<<< orphan*/  conn; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_queue; } ;

/* Variables and functions */
 TYPE_2__* CS ; 
 int CSN ; 
 struct gather_data GDH ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  create_client (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  put_event_into_heap (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

void cron (void) {
  int i, j;
  struct gather_data *G;
  //  flush_binlog();
  for (i = 0; i < CSN; i++) {
    if (!CS[i].conn && now >= CS[i].reconnect_time) {
      j = CS[i].conn_retries++;
      CS[i].reconnect_time = now + (j < 10 ? 1 : 5);
      create_client(CS+i);
    }
  }

  for (G = GDH.next; G != &GDH; G = G->next) {
    assert (G->c);
    if (G->timeout_time <= now) {
      if (verbosity > 0) {
  fprintf (stderr, "gather of master connection %d: TIMEOUT (now=%d, timeout=%d), waking up\n", G->c->fd, now, G->timeout_time);
      }
      if (!G->c->ev->in_queue) {
  put_event_into_heap (G->c->ev);
      }
    }
  }

}