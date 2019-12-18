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
struct list_decoder {int N; int K; int tp; int /*<<< orphan*/ * decode_int; int /*<<< orphan*/  k; int /*<<< orphan*/  br; } ;
typedef  enum list_coding_type { ____Placeholder_list_coding_type } list_coding_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bread_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  degenerate_decode_int ; 
 int /*<<< orphan*/  golomb_decoder_init (struct list_decoder*) ; 
 int /*<<< orphan*/  interpolative_decoder_init (struct list_decoder*) ; 
#define  le_degenerate 133 
#define  le_golomb 132 
#define  le_interpolative 131 
#define  le_interpolative_ext 130 
#define  le_llrun 129 
#define  le_raw_int32 128 
 int /*<<< orphan*/  list_too_short_for_llrun (int,int) ; 
 int /*<<< orphan*/  llrun_decoder_init (struct list_decoder*) ; 
 int /*<<< orphan*/  raw_int32_decoder_init (struct list_decoder*) ; 

__attribute__((used)) static void list_decoder_init (struct list_decoder *dec, int N, int K, const unsigned char *start_ptr, enum list_coding_type tp, int prefix_bit_offset) {
  bread_init (&dec->br, start_ptr, prefix_bit_offset);
  dec->N = N;
  dec->K = K;
  dec->tp = tp;
  switch (tp) {
  case le_golomb:
    golomb_decoder_init (dec);
    break;
  case le_interpolative:
    interpolative_decoder_init (dec);
    break;
  case le_interpolative_ext:
    assert (0);
    break;
  case le_llrun:
    if (list_too_short_for_llrun (N, K)) {
      dec->tp = le_golomb;
      golomb_decoder_init (dec);
    } else {
      llrun_decoder_init (dec);
    }
    break;
  case le_degenerate:
    dec->k = 0;
    dec->decode_int = &degenerate_decode_int;
    break;
  case le_raw_int32:
    raw_int32_decoder_init (dec);
    break;
  default:
    assert (0);
  }
}