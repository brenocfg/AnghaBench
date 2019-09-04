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
struct TYPE_5__ {int user_id; int cat_mask; int /*<<< orphan*/  fr_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_6__ {int cat; } ;
typedef  TYPE_2__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* tree_lookup (int /*<<< orphan*/ ,int) ; 
 int verbosity ; 

__attribute__((used)) static int change_friend_cat (user_t *U, int friend_id, int cat_xor, int cat_and) {
  tree_t *P;
  if (!U || friend_id <= 0) {
    return -1;
  }
  if (verbosity >= 4) {
    fprintf (stderr, "add_friend. user_id = %d, friend_id = %d\n", U->user_id, friend_id);
  }
  P = tree_lookup (U->fr_tree, friend_id);
  if (P) {
    P->cat = ((P->cat & cat_and) ^ cat_xor) | 1;
    U->cat_mask |= P->cat;
    return P->cat;
  } else {
    return 0;
  }
}