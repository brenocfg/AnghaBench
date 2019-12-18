#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ MAX_FRIENDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rev_friends ; 
 int /*<<< orphan*/  rev_friends_find (int /*<<< orphan*/ ,int) ; 
 int rev_friends_intersect_constructive (int /*<<< orphan*/ ,int const,int*,int) ; 
 scalar_t__ rev_friends_intersect_len ; 
 scalar_t__ rev_friends_intersect_pos ; 

int get_common_friends (int user_id, int user_num, const int *userlist, int *resultlist, int max_result) {
  rev_friends_intersect_len = 0;
  rev_friends_find (rev_friends, user_id);
  assert (rev_friends_intersect_len <= MAX_FRIENDS);
  rev_friends_intersect_pos = 0;
  return rev_friends_intersect_constructive (rev_friends, userlist[0], resultlist, max_result);
}