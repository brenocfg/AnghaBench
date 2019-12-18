#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ref_cnt; int /*<<< orphan*/  id; int /*<<< orphan*/ * ev_first; } ;
typedef  TYPE_1__ queue ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ event ;

/* Variables and functions */
 TYPE_2__* event_malloc (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  process_user_query_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_add (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  redirect_news (int /*<<< orphan*/ ,int,int,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int add_event (queue *q, char *data, int data_len, int x, int y, int ttl) {
  if (q == NULL) {
    if (verbosity > 2) {
      fprintf (stderr, "Queue not found.\n");
    }
    return 0;
  }

  //fix
  //dbg ("ADD EVENT: queue name = [%s], data = [%s], ttl = [%d]\n", q->name, data, ttl);

  if (q->ref_cnt != 0 || q->ev_first != NULL) {
    if (verbosity > 2) {
      fprintf (stderr, "  queue = %p\n", q);
    }
    event *e = event_malloc (data_len + 1);

    memcpy (e->data, data, data_len + 1);

    queue_add (q, e);

    process_user_query_queue (q);
  }

  if (ttl) {
    redirect_news (q->id, x, y, ttl, data, data_len);
  }


  return 1;
}