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
struct bitreader {int m; } ;
struct list_decoder {int k; int K; int p; struct bitreader br; scalar_t__ data; } ;
struct interpolative_decoder_stack_entry {int left_idx; int right_idx; void* middle_value; int right_value; int left_value; } ;

/* Variables and functions */
 void* INTERPOLATIVE_DECODER_NOT_EVALUATED ; 
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

__attribute__((used)) static int interpolative_decode_int (struct list_decoder *dec) {
  dec->k++;
  if (dec->k > dec->K) {  /* by K.O.T. */
    return 0x7fffffff;
  }
  struct interpolative_decoder_stack_entry *data = (struct interpolative_decoder_stack_entry *) dec->data + dec->p;
  for (;;) {
    int middle = (data->left_idx + data->right_idx) >> 1;
    if (data->middle_value == INTERPOLATIVE_DECODER_NOT_EVALUATED) {
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
    }
    for (;;) {
      if (dec->k == middle) {
        return data->middle_value;
      }
      if (dec->k < data->right_idx) { break; }
      dec->p--;
      data--;
      middle = (data->left_idx + data->right_idx) >> 1;
    }
    dec->p++;
    struct interpolative_decoder_stack_entry *next = data + 1;
    if (dec->k < middle) {
      next->left_idx = data->left_idx;
      next->left_value = data->left_value;
      next->middle_value = INTERPOLATIVE_DECODER_NOT_EVALUATED;
      next->right_idx = middle;
      next->right_value = data->middle_value;
      data = next;
    } else {
      next->left_idx = middle;
      next->left_value = data->middle_value;
      next->middle_value = INTERPOLATIVE_DECODER_NOT_EVALUATED;
      next->right_idx = data->right_idx;
      next->right_value = data->right_value;
      data = next;
    }
  }
}