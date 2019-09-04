#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct conn_query {int dummy; } ;
struct TYPE_9__ {char* x; TYPE_2__* y; } ;
typedef  TYPE_1__ shmap_pair_string_vptr ;
struct TYPE_10__ {char* name; int /*<<< orphan*/  id; int /*<<< orphan*/ * ev_last; int /*<<< orphan*/  ev_first; struct conn_query* last_q; struct conn_query* first_q; } ;
typedef  TYPE_2__ queue ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  ZERO_UID ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,char*,...) ; 
 scalar_t__ dl_get_memory_used () ; 
 char* dl_strdup (char*) ; 
 int /*<<< orphan*/  get_next_alias () ; 
 int /*<<< orphan*/  h_queue ; 
 scalar_t__ map_ll_vptr_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* queue_malloc () ; 
 TYPE_1__* shmap_string_vptr_add (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__* shmap_string_vptr_get (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  str_memory ; 

inline queue *get_queue (char *name, int force) {
  shmap_pair_string_vptr a, *b;
  a.y = NULL;
  a.x = name;

  queue *q = NULL;
  if (force) {
    b = shmap_string_vptr_add (&h_queue, a);
    if (b->y == NULL) {
      str_memory -= dl_get_memory_used();
      b->x = dl_strdup (b->x);
      str_memory += dl_get_memory_used();

      q = b->y = queue_malloc();

      q->name = b->x;
      q->first_q = q->last_q = (struct conn_query *) q;

      q->ev_first = q->ev_last = NULL; // Yep. It will be list with 'if'

/*      if (get_qtype (name) == Q_NEWS) {
        q->id = get_news_s_id (name);
      } else {*/
        q->id = get_next_alias();
/*      }*/

      dbg ("ALIAS for [%s] = %lld\n", name, q->id);
      ll tid = q->id;

      if (tid == 0) {
        tid = ZERO_UID;
      }

      dbg ("add alias : %lld\n", tid);
      queue **tq = (queue **)map_ll_vptr_add (&alias, tid);
      assert (*tq == NULL);
      *tq = q;
    } else {
      q = b->y;
    }
  } else {
    //fprintf (stderr, "GET queue [%s]\n", name);
    b = shmap_string_vptr_get (&h_queue, a);
    if (b != NULL) {
      q = b->y;
    }
  }

  return q;
}