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
struct list_decoder {int /*<<< orphan*/ * decode_int; scalar_t__ k; int /*<<< orphan*/  N; scalar_t__ K; scalar_t__ data; scalar_t__ p; } ;
struct interpolative_decoder_stack_entry {int left_value; int /*<<< orphan*/  right_value; scalar_t__ right_idx; int /*<<< orphan*/  middle_value; scalar_t__ left_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERPOLATIVE_DECODER_NOT_EVALUATED ; 
 int /*<<< orphan*/  interpolative_decode_int ; 

__attribute__((used)) static void interpolative_decoder_init (struct list_decoder *dec) {
  dec->p = 0;
  struct interpolative_decoder_stack_entry *data = (struct interpolative_decoder_stack_entry *) dec->data;
  data->left_idx = 0;
  data->left_value = -1;
  data->middle_value = INTERPOLATIVE_DECODER_NOT_EVALUATED;
  data->right_idx = dec->K + 1;
  data->right_value = dec->N;
  dec->k = 0;
  dec->decode_int = &interpolative_decode_int;
}