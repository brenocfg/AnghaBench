#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ word; scalar_t__ position; } ;
typedef  TYPE_1__ searchy_pair_word_position_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_word_freq (const void *a, const void *b) {
  const searchy_pair_word_position_t *x = (const searchy_pair_word_position_t *) a,
                                     *y = (const searchy_pair_word_position_t *) b;
  if (x->word < y->word) {
    return -1;
  }
  if (x->word > y->word) {
    return 1;
  }
  return x->position < y->position ? -1 : x->position > y->position ? 1 : 0;
}