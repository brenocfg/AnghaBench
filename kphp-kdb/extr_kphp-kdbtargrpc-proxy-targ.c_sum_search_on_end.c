#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct targ_extra {int mode; int limit; } ;
struct gather {int tot_num; TYPE_1__* List; struct targ_extra* extra; } ;
struct TYPE_5__ {int /*<<< orphan*/  views; int /*<<< orphan*/  ad_id; } ;
typedef  TYPE_2__ gh_entry_t ;
struct TYPE_4__ {scalar_t__ bytes; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GH_total ; 
 int /*<<< orphan*/  TL_VECTOR_TOTAL ; 
 int /*<<< orphan*/  clear_gather_heap (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  gather_heap_advance () ; 
 int gather_heap_insert (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* get_gather_heap_head () ; 
 int /*<<< orphan*/  merge_delete (struct gather*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  received_bad_answers ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int verbosity ; 
 int /*<<< orphan*/  zfree (struct targ_extra*,int) ; 

void sum_search_on_end (struct gather *G) {
  struct targ_extra *e = G->extra;
  if (merge_init_response (G) < 0) {
    zfree (e, sizeof (*e));
    merge_delete (G);
    return;
  }
//  int Q_limit = e->limit;
  int Q_order = (e->mode & 7) | 16;
  if (!(Q_order & 1)) {
    Q_order |= 8;
  }
  clear_gather_heap (Q_order);
 
  int i;
  for (i = 0; i < G->tot_num; i++) if (G->List[i].bytes >= 0) {
    int res = gather_heap_insert (G->List[i].data, G->List[i].bytes);
    if (res < 0) {
      received_bad_answers ++;
    }
  } else {
    if (verbosity >= 4) {
      fprintf (stderr, "Dropping result %d (num = %d)\n", i, G->List[i].bytes);
    }
  }

  tl_store_int (TL_VECTOR_TOTAL);
  tl_store_int (GH_total);
  int *cur = tl_store_get_ptr (4);
  *cur = 0;
  

  while (1) {
    if (*cur >= e->limit) { break; }
    gh_entry_t *H = get_gather_heap_head ();
    if (!H) { break; }
    
    tl_store_int (H->ad_id);
    if (!(Q_order & 8)) {
      tl_store_int (H->views);
    }
    (*cur) ++;
    gather_heap_advance ();
  }
  tl_store_end ();
  zfree (e, sizeof (*e));
  merge_delete (G);
  return;
}