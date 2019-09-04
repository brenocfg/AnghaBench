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
struct TYPE_4__ {scalar_t__ position; scalar_t__ word; } ;
typedef  TYPE_1__ searchy_pair_word_position_t ;
typedef  scalar_t__ hash_t ;

/* Variables and functions */

inline int check_ (searchy_pair_word_position_t *begin, searchy_pair_word_position_t *end, hash_t *needle_begin, hash_t *needle_end) {
  while (begin != end && needle_begin != needle_end) {
    int ok = 0;
    searchy_pair_word_position_t *cur = begin;
    do {
      if (cur->word == needle_begin[0]) {
        ok = 1;
      }
      cur++;
    } while (cur != end && cur->position == begin->position);
    if (!ok) {
      return 0;
    }
    begin = cur;
    needle_begin++;
  }
  return needle_end == needle_begin;
}