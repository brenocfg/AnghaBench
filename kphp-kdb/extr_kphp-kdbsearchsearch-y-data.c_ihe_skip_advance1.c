#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ylist_decoder {scalar_t__ k; } ;
struct list_decoder {scalar_t__ k; int /*<<< orphan*/  (* decode_int ) (struct list_decoder*) ;} ;
struct index_item {int extra; } ;
struct TYPE_7__ {long long item_id; } ;
typedef  TYPE_2__ item_t ;
struct TYPE_6__ {struct list_decoder* tag_dec; struct ylist_decoder* term_dec; } ;
struct TYPE_8__ {scalar_t__ remaining; scalar_t__ len; int /*<<< orphan*/  doc_id; TYPE_1__ dec; scalar_t__ term; } ;
typedef  TYPE_3__ ilist_decoder_t ;
struct TYPE_9__ {TYPE_2__* cur1; TYPE_3__ Decoder; } ;
typedef  TYPE_4__ iheap_en_t ;

/* Variables and functions */
 int FLAG_DELETED ; 
 struct index_item* IndexItems ; 
 int /*<<< orphan*/  list_interpolative_ext_forward_decode_item (struct list_decoder*,long long) ; 
 int /*<<< orphan*/  stub1 (struct list_decoder*) ; 
 int /*<<< orphan*/  ylist_decode_int (struct ylist_decoder*) ; 
 int /*<<< orphan*/  ylist_forward_decode_item (struct ylist_decoder*,long long) ; 

__attribute__((used)) static void ihe_skip_advance1 (iheap_en_t *A, long long item_id) {
  if (A->cur1->item_id >= item_id) {
    return;
  }
  ilist_decoder_t *D = &A->Decoder;
  if (D->term) {
    struct ylist_decoder *dec = D->dec.term_dec;
    D->doc_id = ylist_forward_decode_item (dec, item_id);
    if (D->doc_id < 0) {
      D->remaining = 0;
      A->cur1 = 0;
      return;
    }
    D->remaining = D->len - dec->k;
    for (;;) {
      struct index_item *II = IndexItems + D->doc_id;
      if (!(II->extra & FLAG_DELETED)) {
        A->cur1 = (item_t *) II;
        return;
      }
      if (D->remaining <= 0) {
        D->remaining = 0;
        A->cur1 = 0;
        return;
      }
      D->remaining--;
      D->doc_id = ylist_decode_int (dec);
    }
  } else {
    struct list_decoder *dec = D->dec.tag_dec;
    D->doc_id = list_interpolative_ext_forward_decode_item (dec, item_id);
    if (D->doc_id < 0) {
      D->remaining = 0;
      A->cur1 = 0;
      return;
    }
    D->remaining = D->len - dec->k;
    for (;;) {
      struct index_item *II = IndexItems + D->doc_id;
      if (!(II->extra & FLAG_DELETED)) {
        A->cur1 = (item_t *) II;
        return;
      }
      if (D->remaining <= 0) {
        D->remaining = 0;
        A->cur1 = 0;
        return;
      }
      D->remaining--;
      D->doc_id = dec->decode_int (dec);
    }
  }
}