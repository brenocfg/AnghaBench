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
struct TYPE_5__ {int tot_comments; TYPE_2__* last; } ;
typedef  TYPE_1__ place_t ;
struct TYPE_6__ {int date; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_2__ comment_t ;

/* Variables and functions */
 int COMM_MODE ; 
 int MAX_PLACE_COMMENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_comment (TYPE_2__*) ; 
 int max_news_days ; 
 int now ; 

__attribute__((used)) static int remove_old_comments (place_t *U) {
  assert (COMM_MODE);
  int x = U->tot_comments, y;
  if (!x) {
    return 0;
  }
  y = now - (max_news_days + 1) * 86400;

  comment_t *p = U->last, *q;
  const int old_tot_comments = x;
  while (p != (comment_t *) U && (x > MAX_PLACE_COMMENTS || (p->date & 0x7fffffff) <= y)) {
    q = p->prev;
    free_comment (p);
    x--;
    p = q;
  }
  U->last = p;
  p->next = (comment_t *) U;
  U->tot_comments = x;
  assert (U->tot_comments >= 0);
  return old_tot_comments - x;
}