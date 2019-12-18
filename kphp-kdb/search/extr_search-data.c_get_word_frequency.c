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
typedef  scalar_t__ hash_t ;
struct TYPE_2__ {scalar_t__ word; int len; } ;

/* Variables and functions */
 TYPE_1__* IndexWords ; 
 int idx_words ; 

int get_word_frequency (hash_t word) {
  int a = -1, b = idx_words, c;

  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (IndexWords[c].word <= word) { a = c; } else { b = c; }
  }

  if (a < 0 || IndexWords[a].word != word) {
    return 0;
  }

  return IndexWords[a].len;
}