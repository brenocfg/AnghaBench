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
struct list_decoder {int N; int p; int k; int K; int /*<<< orphan*/  br; scalar_t__ data; } ;
struct interpolative_ext_decoder_stack_entry {int right_value; int left_idx; int right_idx; scalar_t__ right_subtree_offset; int middle_value; int left_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bread_seek (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  interpolative_ext_decode_int (struct list_decoder*) ; 
 int /*<<< orphan*/  interpolative_ext_decode_node (struct list_decoder*,struct interpolative_ext_decoder_stack_entry*) ; 

int list_interpolative_ext_forward_decode_idx (struct list_decoder *dec, int doc_id_lowerbound) {
  if (doc_id_lowerbound >= dec->N) {
    return 0x7fffffff;
  }
  struct interpolative_ext_decoder_stack_entry *data = (struct interpolative_ext_decoder_stack_entry *) dec->data;

  int p = dec->p;
  data += dec->p;
  while (data->right_value <= doc_id_lowerbound) {
    data--;
    p--;
  }

  //fprintf (stderr, "p = %d, dec->p = %d\n", p, dec->p);
  if (p < dec->p) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (data->right_subtree_offset < 0) {
      while (dec->k < middle) {
        interpolative_ext_decode_int (dec);
      }
    } else {
      bread_seek (&dec->br, data->right_subtree_offset);
      dec->k = middle;
    }
    dec->p = p;
  }

  for ( ; ; dec->p++, data++) {
    const int middle = (data->left_idx + data->right_idx) >> 1;
    //fprintf (stderr, "(x[%d] = %d, x[%d] = %d, x[%d] = %d\n", data->left_idx, data->left_value, middle, data->middle_value,  data->right_idx, data->right_value);
    //fprintf (stderr, "dec->k = %d, dec->p = %d\n", dec->k, dec->p);
    if (data->middle_value == doc_id_lowerbound) {
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          interpolative_ext_decode_int (dec);
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
      assert (data->right_value >= doc_id_lowerbound);
      if (data->middle_value < doc_id_lowerbound) {
        if (data->right_idx == dec->K + 1) {
          return 0x7fffffff;
        }
        dec->k = data->right_idx;
        return data->right_value;
      }
      if (data->left_value < doc_id_lowerbound) {
        dec->k = middle;
        return data->middle_value;
      }
      assert (data->left_value >= doc_id_lowerbound);
      dec->k = data->left_idx;
      return data->left_value;
    }
    struct interpolative_ext_decoder_stack_entry *next = data + 1;
    if (data->middle_value > doc_id_lowerbound) {
      //fprintf (stderr, "left\n");
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
      //fprintf (stderr, "right\n");
      if (data->right_subtree_offset < 0) {
        while (dec->k < middle) {
          interpolative_ext_decode_int (dec);
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
  return -1;
}