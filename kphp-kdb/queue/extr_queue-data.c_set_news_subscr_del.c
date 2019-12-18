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
struct TYPE_5__ {int /*<<< orphan*/  subs; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_6__ {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 TYPE_1__* get_news_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_del ; 

int set_news_subscr_del (ll id, ll *a, int n) {
  queue *q = get_news_queue (id, 0);
  if (q == NULL) {
    return 0;
  }
  id = q->id;

  int i;
  for (i = 0; i < n; i++) {
    to_del[i].x = a[i];
  }
  process_changes (id, q->subs, to_del, n, 0, 0);

  return 1;
}