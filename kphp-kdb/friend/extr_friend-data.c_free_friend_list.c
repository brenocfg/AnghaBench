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
struct TYPE_3__ {scalar_t__ fr_cnt; scalar_t__ fr_tree; int /*<<< orphan*/  user_id; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_tree (scalar_t__) ; 
 int /*<<< orphan*/  rev_friends ; 
 int /*<<< orphan*/  rev_friends_delete_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ reverse_friends_mode ; 

__attribute__((used)) static int free_friend_list (user_t *U) {
  if (!U) { return 0; }
  if (reverse_friends_mode) {
    rev_friends = rev_friends_delete_tree (rev_friends, U->user_id, U->fr_tree);
  }
  free_tree (U->fr_tree);
  U->fr_tree = 0;
  U->fr_cnt = 0;
  return 1;
}