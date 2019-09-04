#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  online_tree; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int FRIEND_MULT ; 
 int MAX_USER_FRIENDS ; 
 int /*<<< orphan*/  adjust_online_tree (TYPE_1__*) ; 
 TYPE_1__* get_user_f (int) ; 
 int /*<<< orphan*/  minsert_flag ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  stree_delete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stree_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_history (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

int user_friends_online (int user_id, int N, int *A) {
  user_t *U;
  int i, x = user_id * FRIEND_MULT, c = 0;

  if (N < 0 || N > MAX_USER_FRIENDS || user_id <= 0) {
    return -1;
  }
  if (!N) {
    return 0;
  }

  for (i = 0; i < N; i++) {
    U = get_user_f (A[i]);
    if (!U) {
      continue;
    }
    c++;
    U->online_tree = stree_insert (stree_delete (U->online_tree, x), x, now);
    adjust_online_tree (U);
    if (!minsert_flag) {
      /* send online notification to U->user_id about user_id */
      update_history (U, -user_id, 0, 8);
    }
  }

  return c;
}