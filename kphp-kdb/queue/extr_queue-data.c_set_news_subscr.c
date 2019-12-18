#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ treap ;
struct TYPE_11__ {TYPE_1__* subs; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ queue ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ pli ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  dl_qsort_pli (TYPE_3__*,int) ; 
 TYPE_3__* gd_a ; 
 TYPE_3__* gd_b ; 
 int /*<<< orphan*/  gen_diff_go (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_news_queue (int /*<<< orphan*/ ,int) ; 
 scalar_t__ insert_to_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  news_subscr_actual_len ; 
 int /*<<< orphan*/  news_subscr_cnt ; 
 int news_subscr_len ; 
 int news_subscr_missed ; 
 int /*<<< orphan*/  process_changes (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_add ; 
 scalar_t__ to_add_n ; 
 int /*<<< orphan*/  to_del ; 
 scalar_t__ to_del_n ; 

int set_news_subscr (ll id, pli *a, int n) {
  queue *q = get_news_queue (id, 1);
  if (q == NULL) {
    return 0;
  }
  id = q->id;

  dl_qsort_pli (a, n);

  to_add_n = to_del_n = 0;
  gd_a = a;
  gd_b = a + n;

  news_subscr_len += n;
  news_subscr_cnt++;

  treap *t = q->subs;
  gen_diff_go (t->root);
  while (gd_a != gd_b && insert_to_add (gd_a->x, gd_a->y)) {
    gd_a++;
  }

  /*{
    pli b[100];
    int i;
    int nn = treap_conv_to_array (t->root, b, 100);
    fprintf (stderr, "have <");
    for (i = 0; i < nn; i++) {
      fprintf (stderr, "(%lld;%d)%c", b[i].x, b[i].y, ",>"[i + 1 == nn]);
    }
    fprintf (stderr, "\n");

    fprintf (stderr, "set <");
    for (i = 0; i < n; i++) {
      fprintf (stderr, "(%lld;%d)%c", a[i].x, a[i].y, ",>"[i + 1 == n]);
    }
    fprintf (stderr, "\n");

    fprintf (stderr, "add <");
    for (i = 0; i < to_add_n; i++) {
      fprintf (stderr, "(%lld;%d)%c", to_add[i].x, to_add[i].y, ",>"[i + 1 == to_add_n]);
    }
    fprintf (stderr, "\n");

    fprintf (stderr, "del <");
    for (i = 0; i < to_del_n; i++) {
      fprintf (stderr, "(%lld;%d)%c", to_del[i].x, to_del[i].y, ",>"[i + 1 == to_del_n]);
    }
    fprintf (stderr, "\n");

  }*/

  news_subscr_actual_len += to_del_n + to_add_n;
  news_subscr_missed += (to_del_n + to_add_n) != 0;

  process_changes (id, t, to_del, to_del_n, 0, 0);
  process_changes (id, t, to_add, to_add_n, 1, 0);
  return 1;
}