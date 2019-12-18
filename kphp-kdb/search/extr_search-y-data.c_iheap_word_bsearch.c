#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ word; } ;
typedef  TYPE_1__ iheap_en_t ;
typedef  scalar_t__ hash_t ;

/* Variables and functions */

iheap_en_t *iheap_word_bsearch (iheap_en_t *H, int n, hash_t word) {
  int a = -1, b = n;
  while (b - a > 1) {
    int c = ((a + b) >> 1);
    if (H[c].word <= word) { a = c; } else { b = c; }
  }
  if (a >= 0 && H[a].word == word) {
    return H + a;
  } else {
    return NULL;
  }
}