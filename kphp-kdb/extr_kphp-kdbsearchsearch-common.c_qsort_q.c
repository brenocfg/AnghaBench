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
struct TYPE_3__ {scalar_t__ word; int freqs; } ;
typedef  TYPE_1__ pair_word_freqs_t ;
typedef  scalar_t__ hash_t ;

/* Variables and functions */

__attribute__((used)) static void qsort_q (pair_word_freqs_t *Q, int a, int b) {
  int i, j;
  hash_t h, t;
  int s;
  if (a >= b) { return; }
  h = Q[(a+b)>>1].word;
  i = a;
  j = b;
  do {
    while (Q[i].word < h) { i++; }
    while (Q[j].word > h) { j--; }
    if (i <= j) {
      t = Q[i].word; Q[i].word = Q[j].word; Q[j].word = t;
      s = Q[i].freqs; Q[i].freqs = Q[j].freqs; Q[j].freqs = s;
      i++; j--;
    }
  } while (i <= j);
  qsort_q (Q, a, j);
  qsort_q (Q, i, b);
}