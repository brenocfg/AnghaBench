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
struct mlist_decoder_stack_entry {int left_idx; int right_idx; int right_value; int left_value; int middle_value; int multiplicity; int right_subtree_offset; } ;
struct bitreader {int m; } ;
struct mlist_decoder {scalar_t__ left_subtree_size_threshold; struct bitreader br; scalar_t__ all_ones; } ;

/* Variables and functions */
 int bread_gamma_code (struct bitreader*) ; 
 scalar_t__ bread_get_bitoffset (struct bitreader*) ; 
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

__attribute__((used)) static void mlist_decode_node (struct mlist_decoder *dec, struct mlist_decoder_stack_entry *data) {
  int middle = (data->left_idx + data->right_idx) >> 1;
  const int hi = data->right_value - (data->right_idx - middle);
  int lo = data->left_value + (middle - data->left_idx), r = hi - lo;
  if (r) {
    r++;
    struct bitreader *br = &dec->br;
    int m = br->m;
    int i = 1;
    while (i < r) {
      i <<= 1;
      if (decode_cur_bit) {
        i++;
      }
      decode_load_bit();
    }
    br->m = m;
    i -= r;
    if (i & 1) {
      lo += (r >> 1) - (i >> 1) - 1;
    } else {
      lo += (r >> 1) + (i >> 1);
    }
  }
  data->middle_value = lo;
  if (dec->all_ones) {
    data->multiplicity = 1;
  } else {
    data->multiplicity = bread_gamma_code (&dec->br);
  }
  if (data->right_idx - data->left_idx >= dec->left_subtree_size_threshold) {
    data->right_subtree_offset = bread_gamma_code (&dec->br) - 1;
    data->right_subtree_offset += bread_get_bitoffset (&dec->br);
  } else {
    data->right_subtree_offset = -1;
  }
}