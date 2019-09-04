#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct search_list_decoder {scalar_t__ remaining; scalar_t__ len; TYPE_4__* dec; } ;
struct index_item {int extra; int /*<<< orphan*/  item_id; } ;
struct TYPE_8__ {long long item_id; } ;
typedef  TYPE_1__ item_t ;
struct TYPE_9__ {scalar_t__ doc_id; struct search_list_decoder dec; int /*<<< orphan*/  (* adv_ilist_subseq ) (TYPE_2__*,int) ;int /*<<< orphan*/  item_id; } ;
typedef  TYPE_2__ ilist_decoder_t ;
struct TYPE_10__ {TYPE_1__* cur1; int /*<<< orphan*/  cur_y1; TYPE_2__ Decoder; } ;
typedef  TYPE_3__ iheap_en_t ;
struct TYPE_11__ {scalar_t__ k; int (* decode_int ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int FLAG_DELETED ; 
 struct index_item* IndexItems ; 
 scalar_t__ list_interpolative_ext_forward_decode_item (TYPE_4__*,long long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_4__*) ; 

__attribute__((used)) static void ihe_skip_advance1_fast (iheap_en_t *A, long long item_id) {
  if (A->cur1->item_id >= item_id) {
    return;
  }
  struct search_list_decoder *dec = &A->Decoder.dec;
  ilist_decoder_t *D = &A->Decoder;
  D->doc_id = list_interpolative_ext_forward_decode_item (dec->dec, item_id);
  if (D->doc_id < 0) {
    dec->remaining = 0;
    A->cur1 = 0;
    //A->cur_y1 = 0;
    return;
  }
  dec->remaining = dec->len - dec->dec->k;
  for (;;) {
    struct index_item *II = IndexItems + D->doc_id;
    if (!(II->extra & FLAG_DELETED)) {
      A->cur1 = (item_t *) II;
      D->item_id = II->item_id;
      A->cur_y1 = D->adv_ilist_subseq (D, D->dec.len - 1 - D->dec.remaining);
      return;
    }
    if (dec->remaining <= 0) {
      dec->remaining = 0;
      A->cur1 = 0;
      //A->cur_y1 = 0;
      return;
    }
    dec->remaining--;
    D->doc_id = dec->dec->decode_int (dec->dec);
  }
}