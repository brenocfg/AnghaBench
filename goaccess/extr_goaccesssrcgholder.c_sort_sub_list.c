#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_22__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {int /*<<< orphan*/  nts; } ;
struct TYPE_37__ {int /*<<< orphan*/  nts; } ;
struct TYPE_35__ {int /*<<< orphan*/  nts; } ;
struct TYPE_33__ {int /*<<< orphan*/  nbw; } ;
struct TYPE_40__ {TYPE_8__ maxts; TYPE_6__ cumts; TYPE_4__ avgts; int /*<<< orphan*/  visitors; int /*<<< orphan*/  id; int /*<<< orphan*/  hits; int /*<<< orphan*/  data; TYPE_2__ bw; } ;
struct TYPE_38__ {int /*<<< orphan*/  nts; } ;
struct TYPE_36__ {int /*<<< orphan*/  nts; } ;
struct TYPE_34__ {int /*<<< orphan*/  nts; } ;
struct TYPE_32__ {scalar_t__ serve_usecs; } ;
struct TYPE_31__ {int /*<<< orphan*/  nbw; } ;
struct TYPE_30__ {TYPE_7__ maxts; TYPE_5__ cumts; TYPE_3__ avgts; int /*<<< orphan*/  visitors; int /*<<< orphan*/  id; int /*<<< orphan*/  hits; int /*<<< orphan*/  data; TYPE_1__ bw; } ;
struct TYPE_29__ {int idx; TYPE_10__* items; int /*<<< orphan*/  module; } ;
struct TYPE_28__ {TYPE_18__* metrics; } ;
struct TYPE_27__ {TYPE_9__* metrics; struct TYPE_27__* next; } ;
struct TYPE_26__ {TYPE_12__* head; int /*<<< orphan*/  size; } ;
struct TYPE_25__ {TYPE_11__* sub_list; } ;
typedef  TYPE_11__ GSubList ;
typedef  TYPE_12__ GSubItem ;
typedef  int /*<<< orphan*/  GSort ;
typedef  TYPE_13__ GHolderItem ;
typedef  TYPE_14__ GHolder ;

/* Variables and functions */
 int /*<<< orphan*/  add_sub_item_back (TYPE_11__*,int /*<<< orphan*/ ,TYPE_18__*) ; 
 TYPE_22__ conf ; 
 int /*<<< orphan*/  delete_sub_list (TYPE_11__*) ; 
 int /*<<< orphan*/  free (TYPE_13__*) ; 
 TYPE_13__* new_gholder_item (int /*<<< orphan*/ ) ; 
 TYPE_18__* new_gmetrics () ; 
 TYPE_11__* new_gsublist () ; 
 int /*<<< orphan*/  sort_holder_items (TYPE_13__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sort_sub_list (GHolder * h, GSort sort)
{
  GHolderItem *arr;
  GSubItem *iter;
  GSubList *sub_list;
  int i, j, k;

  /* iterate over root-level nodes */
  for (i = 0; i < h->idx; i++) {
    sub_list = h->items[i].sub_list;
    if (sub_list == NULL)
      continue;

    arr = new_gholder_item (sub_list->size);

    /* copy items from the linked-list into an array */
    for (j = 0, iter = sub_list->head; iter; iter = iter->next, j++) {
      arr[j].metrics = new_gmetrics ();

      arr[j].metrics->bw.nbw = iter->metrics->bw.nbw;
      arr[j].metrics->data = xstrdup (iter->metrics->data);
      arr[j].metrics->hits = iter->metrics->hits;
      arr[j].metrics->id = iter->metrics->id;
      arr[j].metrics->visitors = iter->metrics->visitors;
      if (conf.serve_usecs) {
        arr[j].metrics->avgts.nts = iter->metrics->avgts.nts;
        arr[j].metrics->cumts.nts = iter->metrics->cumts.nts;
        arr[j].metrics->maxts.nts = iter->metrics->maxts.nts;
      }
    }
    sort_holder_items (arr, j, sort);
    delete_sub_list (sub_list);

    sub_list = new_gsublist ();
    for (k = 0; k < j; k++) {
      if (k > 0)
        sub_list = h->items[i].sub_list;

      add_sub_item_back (sub_list, h->module, arr[k].metrics);
      h->items[i].sub_list = sub_list;
    }
    free (arr);
  }
}