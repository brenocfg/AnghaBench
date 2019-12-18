#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_decoder {int p; int k; int K; int /*<<< orphan*/  br; int /*<<< orphan*/  (* decode_int ) (struct list_decoder*) ;scalar_t__ data; } ;
struct interpolative_ext_decoder_stack_entry {size_t right_value; int left_idx; int right_idx; scalar_t__ right_subtree_offset; size_t middle_value; size_t left_value; } ;
struct TYPE_2__ {long long item_id; } ;

/* Variables and functions */
 TYPE_1__* IndexItems ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bread_seek (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  interpolative_ext_decode_node (struct list_decoder*,struct interpolative_ext_decoder_stack_entry*) ; 
 int /*<<< orphan*/  stub1 (struct list_decoder*) ; 
 int /*<<< orphan*/  stub2 (struct list_decoder*) ; 
 int /*<<< orphan*/  stub3 (struct list_decoder*) ; 

__attribute__((used)) static int list_interpolative_ext_forward_decode_item (struct list_decoder *dec, long long item_id_lowerbound) {
  struct interpolative_ext_decoder_stack_entry *data = (struct interpolative_ext_decoder_stack_entry *) dec->data;

  int p = dec->p;
  data += dec->p;
  while (IndexItems[data->right_value].item_id <= item_id_lowerbound) {
    data--;
    p--;
  }

  if (p < dec->p) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (data->right_subtree_offset < 0) {
      while (dec->k < middle) {
        dec->decode_int (dec);
      }
    } else {
      bread_seek (&dec->br, data->right_subtree_offset);
      dec->k = middle;
    }
    dec->p = p;
  }

  for ( ; ; dec->p++, data++) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (IndexItems[data->middle_value].item_id == item_id_lowerbound) {
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          dec->decode_int (dec);
        }
      } else {
        bread_seek (&dec->br, data->right_subtree_offset);
        dec->k = middle;
      }
      return data->middle_value;
    }
    const int l = data->right_idx - data->left_idx;
    assert (l >= 2);
    if (l == 2) {
      assert (IndexItems[data->right_value].item_id >= item_id_lowerbound);
      if (IndexItems[data->middle_value].item_id < item_id_lowerbound) {
        if (data->right_idx == dec->K + 1) {
          return -1;
        }
        dec->k = data->right_idx;
        return data->right_value;
      }
      if (IndexItems[data->left_value].item_id < item_id_lowerbound) {
        dec->k = middle;
        return data->middle_value;
      }
      //assert (data->left_value >= doc_id_lowerbound);
      dec->k = data->left_idx;
      return data->left_value;
    }
    struct interpolative_ext_decoder_stack_entry *next = data + 1;
    if (IndexItems[data->middle_value].item_id > item_id_lowerbound) {
      // left subtree
      if (data->left_idx == middle - 1) {
        dec->k = middle;
        return data->middle_value;
      }
      next->left_idx = data->left_idx;
      next->left_value = data->left_value;
      next->right_idx = middle;
      next->right_value = data->middle_value;
      interpolative_ext_decode_node (dec, next);
    } else {
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          dec->decode_int (dec);
        }
      } else {
        bread_seek (&dec->br, data->right_subtree_offset);
        dec->k = middle;
      }
      next->left_idx = middle;
      next->left_value = data->middle_value;
      next->right_idx = data->right_idx;
      next->right_value = data->right_value;
      interpolative_ext_decode_node (dec, next);
    }
  }
  assert (0);
  return -1;
}