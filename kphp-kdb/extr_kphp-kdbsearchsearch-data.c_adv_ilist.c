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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct index_item {int extra; int /*<<< orphan*/  item_id; } ;
struct TYPE_6__ {scalar_t__ remaining; int len; TYPE_4__* dec; } ;
struct TYPE_7__ {int doc_id; TYPE_1__ dec; int /*<<< orphan*/  item_id; int /*<<< orphan*/  (* adv_ilist_subseq ) (TYPE_2__*,int) ;int /*<<< orphan*/  field; } ;
typedef  TYPE_2__ ilist_decoder_t ;
struct TYPE_8__ {int (* decode_int ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int FLAG_DELETED ; 
 struct index_item* IndexItems ; 
 int /*<<< orphan*/  assert (int) ; 
 int idx_items ; 
 int stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

int adv_ilist (ilist_decoder_t *D) {
  struct index_item *II;
  while (D->dec.remaining > 0) {
    D->dec.remaining--;
    D->doc_id = D->dec.dec->decode_int (D->dec.dec);
    assert (D->doc_id >= 0 && D->doc_id < idx_items);
    II = IndexItems + D->doc_id;
    if (!(II->extra & FLAG_DELETED)) {
      D->item_id = II->item_id;
      D->field = D->adv_ilist_subseq (D, D->dec.len - 1 - D->dec.remaining);
      return D->doc_id;
    }
  }
  if (!D->dec.remaining) {
    D->doc_id = -1;
    D->item_id = 0;
    D->dec.remaining--;
    return -1;
  }
  return -1;
}