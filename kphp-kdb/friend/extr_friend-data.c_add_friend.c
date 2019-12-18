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
struct TYPE_6__ {int user_id; int cat_mask; scalar_t__ fr_cnt; scalar_t__ fr_last_date; int /*<<< orphan*/  fr_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_7__ {int cat; } ;
typedef  TYPE_2__ tree_t ;

/* Variables and functions */
 scalar_t__ MAX_FRIENDS ; 
 int /*<<< orphan*/  delete_friend_request (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  rev_friends ; 
 int /*<<< orphan*/  rev_friends_insert (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reverse_friends_mode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_2__* tree_lookup (int /*<<< orphan*/ ,int) ; 
 int verbosity ; 

__attribute__((used)) static int add_friend (user_t *U, int friend_id, int cat) {
  tree_t *P;
  if (!U || friend_id <= 0) {
    return -1;
  }
  if (verbosity >= 4) {
    fprintf (stderr, "add_friend. user_id = %d, friend_id = %d\n", U->user_id, friend_id);
  }
  P = tree_lookup (U->fr_tree, friend_id);
  if (P) {
    P->cat = cat | 1;
    U->cat_mask |= P->cat;
    return P->cat;
  } else {

    if (U->fr_cnt >= MAX_FRIENDS) {
      return -1;
    }

    delete_friend_request (U, friend_id);

    if (now > U->fr_last_date) {
      U->fr_last_date = now;
    } else {
      U->fr_last_date++;
    }

    U->fr_tree = tree_insert (U->fr_tree, friend_id, lrand48(), cat | 1, U->fr_last_date);
    U->fr_cnt++;

    if (reverse_friends_mode) {
      rev_friends = rev_friends_insert (rev_friends, friend_id, U->user_id, lrand48(), 0);
    }

    return cat | 1;
  }
}