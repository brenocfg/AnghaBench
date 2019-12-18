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
struct TYPE_2__ {scalar_t__* H; int words; scalar_t__ minus_flag; } ;
typedef  TYPE_1__ watchcat_query_phrase_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int memcmp (scalar_t__*,scalar_t__*,int) ; 

inline int cmp_watchcat_query_phrase (const void *x_, const void *y_) {
  const watchcat_query_phrase_t *x = x_;
  const watchcat_query_phrase_t *y = y_;
  if (x->H[0] != y->H[0]) {
    return x->H[0] < y->H[0] ? -1 : +1;
  }
  if (x->words != y->words) {
    return x->words - y->words;
  }
  if (x->minus_flag != y->minus_flag) {
    return x->minus_flag - y->minus_flag;
  }
  return memcmp (x->H, y->H, sizeof (hash_t) * x->words);
}