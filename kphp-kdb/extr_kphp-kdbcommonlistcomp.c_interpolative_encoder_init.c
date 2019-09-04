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
struct list_encoder {int* L; int K; int N; int k; int /*<<< orphan*/ * encode_int; } ;

/* Variables and functions */
 int* malloc (int) ; 
 int /*<<< orphan*/  store_int ; 

__attribute__((used)) static void interpolative_encoder_init (struct list_encoder *enc) {
  enc->L = malloc ( (enc->K + 2) * sizeof (enc->L[0]));
  enc->L[0] = -1;
  enc->L[enc->K+1] = enc->N;
  enc->k = 1;
  enc->encode_int = &store_int;
}