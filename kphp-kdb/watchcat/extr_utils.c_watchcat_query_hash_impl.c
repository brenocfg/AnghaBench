#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int phrases_cnt; TYPE_2__* phrases; } ;
typedef  TYPE_1__ watchcat_query_t ;
struct TYPE_5__ {int words; scalar_t__* H; scalar_t__ minus_flag; } ;
typedef  TYPE_2__ watchcat_query_phrase_t ;

/* Variables and functions */

long long watchcat_query_hash_impl (watchcat_query_t *query) {
  long long query_hash = 0x1234123412341234LL;
  int was_plus = 0;
  int i;
  for (i = 0; i < query->phrases_cnt; i++) {
    watchcat_query_phrase_t *phrase = &query->phrases[i];
    query_hash *= 0x4321432143214321LL;
    long long phrase_hash = 0x1234567812345678LL;
    if (phrase->minus_flag) {
      phrase_hash++;
    } else {
      was_plus = 1;
    }
    phrase_hash += phrase->minus_flag;
    int j;
    for (j = 0; j < phrase->words; j++) {
      phrase_hash *= 0x8765432187654321LL;
      phrase_hash += phrase->H[j];
    }

    query_hash += phrase_hash;
  }

  if (!was_plus) {
    //bad query
    /*printf ("Bad query\n");*/
    return -1;
  }

  return query_hash;
}