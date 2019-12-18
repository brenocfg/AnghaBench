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
struct list_decoder {int N; int K; int size; int /*<<< orphan*/  tp; int /*<<< orphan*/ * decode_int; scalar_t__ k; int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int /*<<< orphan*/  bread_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  degenerate_decode_int ; 
 int /*<<< orphan*/  golomb_decoder_init (struct list_decoder*) ; 
 int /*<<< orphan*/  le_degenerate ; 
 int /*<<< orphan*/  le_golomb ; 

void golomb_list_decoder_init (struct list_decoder *dec, int N, int K, const unsigned char *start_ptr, int prefix_bit_offset) {
  bread_init (&dec->br, start_ptr, prefix_bit_offset);
  dec->N = N;
  dec->K = K;
  dec->size = sizeof (struct list_decoder);
  if (K == N) {
    dec->tp = le_degenerate;
    dec->k = 0;
    dec->decode_int = &degenerate_decode_int;
  } else {
    dec->tp = le_golomb;
    golomb_decoder_init (dec);
  }
}