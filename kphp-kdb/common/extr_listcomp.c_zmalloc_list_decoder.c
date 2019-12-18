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
struct list_decoder {int p; int size; } ;
struct interpolative_decoder_stack_entry {int dummy; } ;
typedef  enum list_coding_type { ____Placeholder_list_coding_type } list_coding_type ;

/* Variables and functions */
 int /*<<< orphan*/  HUFFMAN_MAX_CODE_LENGTH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsr (int) ; 
 int /*<<< orphan*/  get_max_possible_gap (int,int) ; 
#define  le_degenerate 133 
#define  le_golomb 132 
#define  le_interpolative 131 
#define  le_interpolative_ext 130 
#define  le_llrun 129 
#define  le_raw_int32 128 
 int /*<<< orphan*/  list_decoder_init (struct list_decoder*,int,int,unsigned char const*,int,int) ; 
 int llrun_get_buckets_quantity (int /*<<< orphan*/ ) ; 
 struct list_decoder* zmalloc (int) ; 

struct list_decoder *zmalloc_list_decoder (int N, int K, const unsigned char *start_ptr, enum list_coding_type tp, int prefix_bit_offset) {
  int p = 0, sz = sizeof (struct list_decoder);
  if (N == K) {
    tp = le_degenerate;
  }
  switch (tp) {
  case le_golomb:
  case le_degenerate:
    break;
  case le_interpolative:
    sz += sizeof (struct interpolative_decoder_stack_entry) * (bsr (K+1) + 1);
    break;
  case le_interpolative_ext:
    assert (0);
    break;
  case le_llrun:
    p = llrun_get_buckets_quantity (get_max_possible_gap (N, K));
    sz += ((HUFFMAN_MAX_CODE_LENGTH + 1) + (p + 1) * (HUFFMAN_MAX_CODE_LENGTH + 1)) * sizeof (int);
    break;
  case le_raw_int32:
    break;
  }
  struct list_decoder *dec = zmalloc (sz);
  dec->p = p;
  dec->size = sz;
  list_decoder_init (dec, N, K, start_ptr, tp, prefix_bit_offset);
  return dec;
}