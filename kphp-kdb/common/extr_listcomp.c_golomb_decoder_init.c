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
struct list_decoder {int M; int p; int k; int last; int /*<<< orphan*/ * decode_int; int /*<<< orphan*/  K; int /*<<< orphan*/  N; } ;

/* Variables and functions */
 int bsr (int const) ; 
 int compute_golomb_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  golomb_decode_int_big_k ; 
 int /*<<< orphan*/  golomb_decode_int_small_k ; 

__attribute__((used)) static void golomb_decoder_init (struct list_decoder *dec) {
  const int M = compute_golomb_parameter (dec->N, dec->K);
  dec->M = M;
  dec->p = (1 << (dec->k = bsr (M) + 1)) - M;
  dec->last = -1;
  dec->decode_int = dec->k > 1 ? &golomb_decode_int_big_k : &golomb_decode_int_small_k;
}