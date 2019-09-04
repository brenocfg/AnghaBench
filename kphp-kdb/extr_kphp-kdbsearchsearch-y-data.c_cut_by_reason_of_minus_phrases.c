#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int words; TYPE_2__** E; } ;
typedef  TYPE_1__ searchy_iheap_phrase_t ;
struct TYPE_7__ {long long item_id; } ;
typedef  TYPE_2__ iheap_en_t ;

/* Variables and functions */
 TYPE_1__* Phrases ; 
 int /*<<< orphan*/  ihe_skip_advance (TYPE_2__*,long long) ; 
 scalar_t__ phrase_count_extra_words (TYPE_1__*) ; 

__attribute__((used)) static inline int cut_by_reason_of_minus_phrases (long long item_id, int plus_phrases, int phrases) {
  int i;
  for (i = plus_phrases; i < phrases; i++) {
    int j;
    searchy_iheap_phrase_t *A = &Phrases[i];
    for (j = 0; j < A->words; j++) {
      iheap_en_t *I = A->E[j];
      if (I->item_id < item_id) {
        ihe_skip_advance (I, item_id);
      }
      if (I->item_id > item_id) {
        goto next_phrase;
      }
    }
    if (A->words < 2 || phrase_count_extra_words (A) <= 0) {
      return 1;
    }
    next_phrase:;
  }
  return 0;
}