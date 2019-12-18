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
struct TYPE_3__ {int x1; struct TYPE_3__* right; int /*<<< orphan*/  x2; struct TYPE_3__* left; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */
 scalar_t__ MAX_FRIENDS ; 
 scalar_t__ rev_friends_intersect_len ; 
 int /*<<< orphan*/ * rev_friends_intersect_list ; 

__attribute__((used)) static void rev_friends_find (rev_friends_t *T, int x1) {
  if (!T) {
    return;
  }
  if (T->x1 >= x1) {
    rev_friends_find (T->left, x1);
  }
  if (T->x1 == x1 && rev_friends_intersect_len < MAX_FRIENDS) {
    rev_friends_intersect_list[rev_friends_intersect_len++] = T->x2;
  }
  if (T->x1 <= x1) {
    rev_friends_find (T->right, x1);
  }
}