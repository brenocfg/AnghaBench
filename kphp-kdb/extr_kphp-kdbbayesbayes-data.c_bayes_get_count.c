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
struct TYPE_5__ {int spam; int ham; } ;
typedef  TYPE_1__ pair ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_6__ {int /*<<< orphan*/  cnt; } ;
typedef  TYPE_2__ bayes ;

/* Variables and functions */
 int SPAM ; 
 TYPE_1__* qhtbl_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int bayes_get_count (bayes *b, ll word, int type) {
  pair *tmp = qhtbl_get (&b->cnt, word);
  if (tmp == NULL)
    return 0;
  if (type == SPAM) {
    return tmp->spam;
  } else {
    return tmp->ham;
  }
}