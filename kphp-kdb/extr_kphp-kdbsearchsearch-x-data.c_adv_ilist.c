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
struct list_decoder {int (* decode_int ) (struct list_decoder*) ;int /*<<< orphan*/  br; } ;
struct index_item {int extra; int /*<<< orphan*/  item_id; } ;
struct TYPE_4__ {scalar_t__ remaining; struct list_decoder* dec; } ;
struct TYPE_5__ {int doc_id; unsigned int freq_title; unsigned int freq_text; TYPE_1__ dec; int /*<<< orphan*/  item_id; } ;
typedef  TYPE_2__ ilist_decoder_t ;

/* Variables and functions */
 int FLAG_DELETED ; 
 struct index_item* IndexItems ; 
 int /*<<< orphan*/  assert (int) ; 
 int bread_gamma_code (int /*<<< orphan*/ *) ; 
 int idx_items ; 
 int stub1 (struct list_decoder*) ; 

__attribute__((used)) static int adv_ilist (ilist_decoder_t *D) {
  struct index_item *II;
  while (D->dec.remaining > 0) {
    struct list_decoder *dec = D->dec.dec;
    D->dec.remaining--;
    D->doc_id = dec->decode_int (D->dec.dec);
    assert (D->doc_id >= 0 && D->doc_id < idx_items);
    unsigned freq1 = bread_gamma_code (&dec->br) - 1;
    unsigned freq2 = bread_gamma_code (&dec->br) - 1;
    II = IndexItems + D->doc_id;
    if (!(II->extra & FLAG_DELETED)) {
      if (!freq1) { freq2++; }
      D->item_id = II->item_id;
      D->freq_title = freq1;
      D->freq_text = freq2;
      return D->doc_id;
    }
  }
  if (!D->dec.remaining) {
    D->doc_id = -1;
    D->item_id = 0;
    D->freq_title = D->freq_text = 0;
    D->dec.remaining--;
    return -1;
  }
  return -1;
}