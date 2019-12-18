#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int phrases_cnt; TYPE_2__* phrases; } ;
typedef  TYPE_1__ watchcat_query_t ;
struct TYPE_12__ {int words; int /*<<< orphan*/ * H; scalar_t__ minus_flag; } ;
typedef  TYPE_2__ watchcat_query_phrase_t ;
struct TYPE_13__ {long long id; scalar_t__ vn; int /*<<< orphan*/  keys; TYPE_1__* query; } ;
typedef  TYPE_3__ watchcat ;

/* Variables and functions */
 TYPE_3__* alloc_watchcat () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long) ; 
 int /*<<< orphan*/  free_watchcat_query (TYPE_1__*) ; 
 TYPE_3__* get_watchcat_q (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h_watchcat ; 
 scalar_t__ hset_llp_add (int /*<<< orphan*/ *,long long*) ; 
 int my_verbosity ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  watchcat_q_add (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  wkey_set_init (int /*<<< orphan*/ *) ; 

inline watchcat *get_watchcat (long long id, watchcat_query_t *query) {
  watchcat **b;
  b = (watchcat **)hset_llp_add (&h_watchcat, &id);
  if (*b == (watchcat *)&id) {
    watchcat *w = alloc_watchcat();
    w->id = id;
    w->query = query;

    wkey_set_init (&w->keys);

    if (my_verbosity > 1) {
      fprintf (stderr, "watchcat_created id = %lld\n", id);
    }

    int i;
    watchcat *bq = NULL;

    int done = 0;
    for (i = 0; i < query->phrases_cnt && !done; i++) {
      watchcat_query_phrase_t *phrase = &query->phrases[i];
      if (phrase->minus_flag) {
        continue;
      }
      int j;
      for (j = 0; j < phrase->words && !done; j++) {
        watchcat *q = get_watchcat_q (phrase->H[j], 1);
        if (bq == NULL || bq->vn > q->vn) {
          bq = q;
        }
        if (bq->vn == 0) {
          done = 1;
        }
      }
    }

    assert (bq != NULL);
    if (my_verbosity > 1) {
      fprintf (stderr, "added to %lld queue\n", bq->id);
    }
    watchcat_q_add (bq, w);

    *b = w;
  } else {
    free_watchcat_query (query);
  }
  return *b;
}