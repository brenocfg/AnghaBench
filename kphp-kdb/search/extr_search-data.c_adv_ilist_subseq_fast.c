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
struct TYPE_4__ {int /*<<< orphan*/  dec; } ;
struct TYPE_5__ {int last_subseq; TYPE_1__ dec_subseq; } ;
typedef  TYPE_2__ ilist_decoder_t ;

/* Variables and functions */
 int list_interpolative_ext_forward_decode_idx (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adv_ilist_subseq_fast (ilist_decoder_t *D, int idx) {
  D->last_subseq = list_interpolative_ext_forward_decode_idx (D->dec_subseq.dec, idx);
  return (D->last_subseq == idx) ? 1 : 0;
}