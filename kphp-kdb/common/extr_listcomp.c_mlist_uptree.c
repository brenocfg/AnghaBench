#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlist_decoder_stack_entry {int left_idx; int right_idx; int multiplicity; } ;
struct mlist_decoder {int k; scalar_t__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void mlist_uptree (struct mlist_decoder *dec, struct mlist_decoder_stack_entry *data, int idx, int *multiplicity) {
  dec->k = idx;
  for (;;) {
    data--;
    (dec->p)--;
    assert (dec->p >= 0);
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (middle == idx) {
      *multiplicity = data->multiplicity;
      return;
    }
  }
}