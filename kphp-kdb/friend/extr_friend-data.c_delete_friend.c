#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int user_id; scalar_t__ fr_cnt; int /*<<< orphan*/  fr_tree; } ;
typedef  TYPE_1__ user_t ;
typedef  int /*<<< orphan*/  tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rev_friends ; 
 int /*<<< orphan*/  rev_friends_delete (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ reverse_friends_mode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tree_delete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tree_lookup (int /*<<< orphan*/ ,int) ; 
 int verbosity ; 

__attribute__((used)) static int delete_friend (user_t *U, int friend_id) {
  tree_t *P;
  if (!U || friend_id <= 0) {
    return -1;
  }
  if (verbosity >= 4) {
    fprintf (stderr, "delete_friend. user_id = %d, friend_id = %d\n", U->user_id, friend_id);
  }
  P = tree_lookup (U->fr_tree, friend_id);
  if (P) {
    U->fr_tree = tree_delete (U->fr_tree, friend_id);
    U->fr_cnt--;
    assert (U->fr_cnt >= 0);
    if (reverse_friends_mode) {
      rev_friends = rev_friends_delete (rev_friends, friend_id, U->user_id);
    }
    return 1;
  }
  return 0;
}