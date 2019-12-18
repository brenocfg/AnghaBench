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
struct list_encoder {int k; int p; int M; int last; int /*<<< orphan*/ * encode_int; int /*<<< orphan*/  K; int /*<<< orphan*/  N; } ;

/* Variables and functions */
 int compute_golomb_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  golomb_encode_int ; 

__attribute__((used)) static void golomb_encoder_init (struct list_encoder *enc) {
  int M = compute_golomb_parameter (enc->N, enc->K);
  enc->k = 31;
  enc->p = 1;
  while (enc->p <= M) {
    enc->p *= 2;
    enc->k--;
  }
  enc->p -= M;
  enc->M = M;
  enc->last = -1;
  enc->encode_int = &golomb_encode_int;
}