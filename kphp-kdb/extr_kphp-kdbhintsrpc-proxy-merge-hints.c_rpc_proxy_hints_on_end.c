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
struct hints_extra {int limit; scalar_t__ op; scalar_t__ sent_op; } ;
struct gather {int tot_num; struct hints_extra* extra; TYPE_1__* List; } ;
struct TYPE_5__ {int /*<<< orphan*/  rating; int /*<<< orphan*/  object_id; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ gh_entry_t ;
struct TYPE_4__ {scalar_t__ bytes; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GH_total ; 
 int /*<<< orphan*/  TL_VECTOR_TOTAL ; 
 int /*<<< orphan*/  clear_gather_heap () ; 
 int /*<<< orphan*/  free (struct hints_extra*) ; 
 int /*<<< orphan*/  gather_heap_advance () ; 
 int gather_heap_insert (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* get_gather_heap_head () ; 
 int /*<<< orphan*/  merge_delete (struct gather*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  received_bad_answers ; 
 int /*<<< orphan*/  tl_store_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,scalar_t__) ; 

void rpc_proxy_hints_on_end (struct gather *G) {
  struct hints_extra *extra = G->extra;
  clear_gather_heap ();
  int i;
  for (i = 0; i < G->tot_num; i++) {
    if (G->List[i].bytes >= 0) {
      int res = gather_heap_insert (G->List[i].data, G->List[i].bytes);
      if (res < 0) {
        received_bad_answers++;
      }
    } else {
      vkprintf (4, "Dropping result %d (num = %d)\n", i, G->List[i].bytes);
    }
  }

  if (merge_init_response (G)) {
    tl_store_int (TL_VECTOR_TOTAL);
    tl_store_int (GH_total);
    int *x = tl_store_get_ptr (4);

    for (i = 0; i < extra->limit; i++) {
      gh_entry_t *H = get_gather_heap_head ();
      if (H == NULL) {
        break;
      }

      tl_store_int (H->type);
      tl_store_int (H->object_id);
      if (extra->op == extra->sent_op) {
        tl_store_double (H->rating);
      }

      gather_heap_advance ();
    }

    *x = i;
    tl_store_end ();
  }

  free (G->extra);
  merge_delete (G);
  return;
}