#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  x; int /*<<< orphan*/ * next_time; TYPE_2__* parent; } ;
typedef  TYPE_1__ wkey ;
struct TYPE_12__ {scalar_t__ size; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; struct TYPE_11__* next; TYPE_5__ keys; } ;
typedef  TYPE_2__ watchcat ;

/* Variables and functions */
 int /*<<< orphan*/  del_entry_time (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_watchcat (TYPE_2__*) ; 
 int /*<<< orphan*/  free_watchcat_q (TYPE_2__*) ; 
 int /*<<< orphan*/  h_watchcat ; 
 int /*<<< orphan*/  h_watchcat_q ; 
 int /*<<< orphan*/  hset_llp_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int my_verbosity ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  trp_del (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* watchcat_q_del (TYPE_2__*) ; 

inline void del_wkey (wkey *k) {
  watchcat *w = k->parent;

  if (k->next_time != NULL) {
    del_entry_time (k);
  }

  trp_del (&w->keys, k->x);

  //TODO can we replace next line with if (w->keys.root == NULL) and delete size from set
  if (w->keys.size == 0) {
    watchcat *q = watchcat_q_del (w);

    if (q->next == q) {
      hset_llp_del (&h_watchcat_q, &q->id);
      free_watchcat_q (q);
    }

    if (my_verbosity > 1) {
      fprintf (stderr, "Del watchcat %lld\n", w->id);
    }

    hset_llp_del (&h_watchcat, &w->id);
    free_watchcat (w);
  }
}