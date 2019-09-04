#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct index_item {int extra; } ;
struct TYPE_5__ {TYPE_3__* tag_dec; int /*<<< orphan*/  term_dec; } ;
struct TYPE_6__ {scalar_t__ remaining; int doc_id; TYPE_1__ dec; scalar_t__ term; } ;
typedef  TYPE_2__ ilist_decoder_t ;
struct TYPE_7__ {int (* decode_int ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int FLAG_DELETED ; 
 struct index_item* IndexItems ; 
 int /*<<< orphan*/  assert (int) ; 
 int idx_items ; 
 int stub1 (TYPE_3__*) ; 
 int ylist_decode_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv_ilist (ilist_decoder_t *D) {
  while (D->remaining > 0) {
    D->remaining--;
    D->doc_id = D->term ? ylist_decode_int (D->dec.term_dec) : D->dec.tag_dec->decode_int (D->dec.tag_dec);
    assert (D->doc_id >= 0 && D->doc_id < idx_items);
    struct index_item *II = IndexItems + D->doc_id;
    if (!(II->extra & FLAG_DELETED)) {
      return D->doc_id;
    }
  }
  return D->doc_id = -1;
}