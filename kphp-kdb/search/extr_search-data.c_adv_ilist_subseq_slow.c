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
struct search_list_decoder {scalar_t__ remaining; TYPE_2__* dec; } ;
struct TYPE_4__ {int last_subseq; struct search_list_decoder dec_subseq; } ;
typedef  TYPE_1__ ilist_decoder_t ;
struct TYPE_5__ {int (* decode_int ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int adv_ilist_subseq_slow (ilist_decoder_t *D, int idx) {
  struct search_list_decoder *dec_subseq = &D->dec_subseq;
  while (D->last_subseq < idx) {
    if (dec_subseq->remaining <= 0) {
      D->last_subseq = 0x7fffffff;
      return 0;
    }
    dec_subseq->remaining--;
    D->last_subseq = dec_subseq->dec->decode_int (dec_subseq->dec);
  }
  return (D->last_subseq == idx) ? 1 : 0;
}