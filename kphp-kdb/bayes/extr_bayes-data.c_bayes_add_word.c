#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ham; int spam; } ;
typedef  TYPE_1__ pair ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_6__ {int /*<<< orphan*/  cnt; } ;
typedef  TYPE_2__ bayes ;

/* Variables and functions */
 TYPE_1__* qhtbl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bayes_add_word (bayes *b, ll word, int add_ham, int add_spam) {
  pair *tmp;
  tmp = qhtbl_add (&b->cnt, word);
  tmp->ham += add_ham;
  tmp->spam += add_spam;

  if (tmp->ham > 1000000000 || tmp->spam > 1000000000) {
    tmp->ham /= 2;
    tmp->spam /= 2;
  }

  if (tmp->ham < 0) {
    tmp->ham = 0;
  }

  if (tmp->spam < 0) {
    tmp->spam = 0;
  }

  return;
}