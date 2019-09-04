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
struct TYPE_2__ {double weight; } ;

/* Variables and functions */
 scalar_t__ IHT ; 
 scalar_t__ MAX_OPTIONAL_TAGS ; 
 int MAX_PRIORITY ; 
 scalar_t__* QOTW ; 
 TYPE_1__ QRP ; 
 scalar_t__* QT ; 
 int /*<<< orphan*/ * QW ; 
 int Q_K_Opt_Tag ; 
 scalar_t__ Q_optional_tags ; 
 int Q_words ; 
 scalar_t__ ihe_init (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 double optional_tags_mult_coeff ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,scalar_t__) ; 

__attribute__((used)) static void optional_tags_init (void) {
  int i, tot_opt_tags = 0;
  Q_optional_tags = 0;
  for (i = 0; i < Q_words; i++) {
    if (!QT[i]) {
      break;
    }
  }
  const int first_words_idx = i;
  int tot_optinal_tags_weight = 0;
  if (i < Q_words) {
    /* extract optional tags */
    while (Q_words > 0 && Q_optional_tags < MAX_OPTIONAL_TAGS) {
      if (QT[Q_words - 1]) {
        Q_words--;
        if (ihe_init (IHT+Q_optional_tags, QW[Q_words], 1, QOTW[Q_words])) {
          Q_optional_tags++;
          tot_optinal_tags_weight += QOTW[Q_words];
        }
        tot_opt_tags++;
      } else {
        break;
      }
    }
  }
  optional_tags_mult_coeff = 1.0 / (1.0 + Q_K_Opt_Tag * tot_optinal_tags_weight);
  vkprintf (3, "Q_words = %d, optinal_tags = %d\n", Q_words, Q_optional_tags);
  int words = Q_words - first_words_idx;
  if (words > MAX_PRIORITY) {
    words = MAX_PRIORITY;
  }
  if (words > 0) {
    QRP.weight /= (double) words;
  }
}