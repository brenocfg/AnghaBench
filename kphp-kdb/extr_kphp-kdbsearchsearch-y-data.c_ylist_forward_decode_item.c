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
struct ylist_decoder_stack_entry {int right_value; int left_idx; int right_idx; scalar_t__ right_subtree_offset; int middle_value; int left_value; } ;
struct ylist_decoder {int p; int k; int K; int /*<<< orphan*/  br; struct ylist_decoder_stack_entry* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bread_seek (int /*<<< orphan*/ *,scalar_t__) ; 
 long long docid_to_itemid (int) ; 
 int /*<<< orphan*/  ylist_copy_positions (struct ylist_decoder*,struct ylist_decoder_stack_entry*) ; 
 int /*<<< orphan*/  ylist_decode_int (struct ylist_decoder*) ; 
 int /*<<< orphan*/  ylist_decode_node (struct ylist_decoder*,struct ylist_decoder_stack_entry*) ; 
 int /*<<< orphan*/  ylist_uptree (struct ylist_decoder*,struct ylist_decoder_stack_entry*,int) ; 

int ylist_forward_decode_item (struct ylist_decoder *dec, long long item_id_lowerbound) {
  struct ylist_decoder_stack_entry *data = dec->stack;

  int p = dec->p;
  data += dec->p;
  while (docid_to_itemid (data->right_value) <= item_id_lowerbound) {
    data--;
    p--;
  }

  if (p < dec->p) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (data->right_subtree_offset < 0) {
      while (dec->k < middle) {
        ylist_decode_int (dec);
      }
    } else {
      bread_seek (&dec->br, data->right_subtree_offset);
      dec->k = middle;
    }
    dec->p = p;
  }

  for ( ; ; dec->p++, data++) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (docid_to_itemid (data->middle_value) == item_id_lowerbound) {
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          ylist_decode_int (dec);
        }
      } else {
        bread_seek (&dec->br, data->right_subtree_offset);
        dec->k = middle;
      }
      ylist_copy_positions (dec, data);
      return data->middle_value;
    }
    const int l = data->right_idx - data->left_idx;
    assert (l >= 2);
    if (l == 2) {
      assert (docid_to_itemid (data->right_value) >= item_id_lowerbound);
      if (docid_to_itemid (data->middle_value) < item_id_lowerbound) {
        if (data->right_idx == dec->K + 1) {
          return -1;
        }
        ylist_uptree (dec, data, data->right_idx);
        return data->right_value;
      }
      if (docid_to_itemid (data->left_value) < item_id_lowerbound) {
        dec->k = middle;
        ylist_copy_positions (dec, data);
        return data->middle_value;
      }
      //assert (data->left_value >= doc_id_lowerbound);
      ylist_uptree (dec, data, data->left_idx);
      return data->left_value;
    }
    struct ylist_decoder_stack_entry *next = data + 1;
    if (docid_to_itemid (data->middle_value) > item_id_lowerbound) {
      // left subtree
      if (data->left_idx == middle - 1) {
        dec->k = middle;
        ylist_copy_positions (dec, data);
        return data->middle_value;
      }
      next->left_idx = data->left_idx;
      next->left_value = data->left_value;
      next->right_idx = middle;
      next->right_value = data->middle_value;
      ylist_decode_node (dec, next);
    } else {
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          ylist_decode_int (dec);
        }
      } else {
        bread_seek (&dec->br, data->right_subtree_offset);
        dec->k = middle;
      }
      next->left_idx = middle;
      next->left_value = data->middle_value;
      next->right_idx = data->right_idx;
      next->right_value = data->right_value;
      ylist_decode_node (dec, next);
    }
  }
  assert (0);
  return -1;
}