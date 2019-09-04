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

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ Phrases ; 
 int phrase_count_extra_words (scalar_t__) ; 

__attribute__((used)) static int count_max_extra_words (int Q_phrases, int max_extra_words) {
  int i, r = 0;
  for (i = 0; i < Q_phrases; i++) {
    int w = phrase_count_extra_words (Phrases + i);
    if (w > max_extra_words) {
      return INT_MAX;
    }
    if (r < w) {
      r = w;
    }
  }
  return r;
}