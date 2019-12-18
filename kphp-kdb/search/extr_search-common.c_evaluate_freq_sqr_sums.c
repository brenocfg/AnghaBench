#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int freqs; } ;
typedef  TYPE_1__ pair_word_freqs_t ;

/* Variables and functions */

void evaluate_freq_sqr_sums (pair_word_freqs_t *Q, int n, unsigned *sum_sqr_freq_title, unsigned *sum_freq_title_freq_text, unsigned *sum_sqr_freq_text) {
  int i;
  *sum_sqr_freq_title = *sum_freq_title_freq_text = *sum_sqr_freq_text = 0;
  for (i = 0; i < n; i++) {
    unsigned freq_title = Q[i].freqs >> 16, freq_text = Q[i].freqs & 0xffff;
    *sum_sqr_freq_title += freq_title * freq_title;
    *sum_freq_title_freq_text += freq_title * freq_text;
    *sum_sqr_freq_text += freq_text * freq_text;
  }
}