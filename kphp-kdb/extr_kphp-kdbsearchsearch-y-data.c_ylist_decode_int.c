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
struct ylist_decoder_stack_entry {int left_idx; int right_idx; int middle_value; int left_value; int right_value; } ;
struct ylist_decoder {int k; int K; int p; struct ylist_decoder_stack_entry* stack; scalar_t__* positions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ylist_copy_positions (struct ylist_decoder*,struct ylist_decoder_stack_entry*) ; 
 int /*<<< orphan*/  ylist_decode_node (struct ylist_decoder*,struct ylist_decoder_stack_entry*) ; 

int ylist_decode_int (struct ylist_decoder *dec) {
  if (dec->k >= dec->K) {
    dec->positions[0] = 0;
    return 0x7fffffff;
  }
  dec->k++;
  struct ylist_decoder_stack_entry *data = dec->stack + dec->p;
  for (;;) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    for (;;) {
      if (dec->k == middle) {
        ylist_copy_positions (dec, data);
        return data->middle_value;
      }
      if (dec->k < data->right_idx) { break; }
      dec->p--;
      data--;
      middle = (data->left_idx + data->right_idx) >> 1;
    }
    dec->p++;
    struct ylist_decoder_stack_entry *next = data + 1;
    if (dec->k < middle) {
      next->left_idx = data->left_idx;
      next->left_value = data->left_value;
      next->right_idx = middle;
      next->right_value = data->middle_value;
      ylist_decode_node (dec, next);
      data = next;
    } else {
      next->left_idx = middle;
      next->left_value = data->middle_value;
      next->right_idx = data->right_idx;
      next->right_value = data->right_value;
      ylist_decode_node (dec, next);
      data = next;
    }
  }
}