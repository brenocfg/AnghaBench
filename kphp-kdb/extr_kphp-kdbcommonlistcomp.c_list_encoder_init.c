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
struct list_encoder {int N; int K; int tp; int /*<<< orphan*/ * encode_int; scalar_t__ k; int /*<<< orphan*/  bw; } ;
typedef  enum list_coding_type { ____Placeholder_list_coding_type } list_coding_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwrite_init (int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  degenerate_encode_int ; 
 int /*<<< orphan*/  golomb_encoder_init (struct list_encoder*) ; 
 int /*<<< orphan*/  interpolative_encoder_init (struct list_encoder*) ; 
 int le_degenerate ; 
#define  le_golomb 130 
#define  le_interpolative 129 
#define  le_llrun 128 
 int /*<<< orphan*/  list_too_short_for_llrun (int,int) ; 
 int /*<<< orphan*/  llrun_encoder_init (struct list_encoder*) ; 

void list_encoder_init (struct list_encoder *enc, int N, int K, unsigned char *ptr, unsigned char *end_ptr, enum list_coding_type tp, int prefix_bit_offset) {
  bwrite_init (&enc->bw, ptr, end_ptr, prefix_bit_offset);
  enc->N = N;
  enc->K = K;
  if (N == K) {
    enc->tp = le_degenerate;
    enc->k = 0;
    enc->encode_int = &degenerate_encode_int;
    return;
  }
  enc->tp = tp;
  switch (tp) {
  case le_golomb:
    golomb_encoder_init (enc);
    return;
  case le_interpolative:
    interpolative_encoder_init (enc);
    return;
  case le_llrun:
    if (list_too_short_for_llrun (N, K)) {
      enc->tp = le_golomb;
      golomb_encoder_init (enc);
    } else {
      llrun_encoder_init (enc);
    }
    return;
  default:
    assert (0);
  }
}