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
struct TYPE_3__ {int x1; scalar_t__ x2; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */
 size_t rev_friends_intersect_len ; 
 scalar_t__* rev_friends_intersect_list ; 
 size_t rev_friends_intersect_pos ; 

__attribute__((used)) static int rev_friends_intersect (rev_friends_t *T, int x1) {
  if (!T) {
    return 0;
  }
  int result = 0;
  if (T->x1 >= x1) {
    result += rev_friends_intersect (T->left, x1);
  }
  if (T->x1 == x1) {
    while (rev_friends_intersect_pos < rev_friends_intersect_len && rev_friends_intersect_list[rev_friends_intersect_pos] < T->x2) {
      rev_friends_intersect_pos ++;
    }
    if (rev_friends_intersect_pos < rev_friends_intersect_len && rev_friends_intersect_list[rev_friends_intersect_pos] == T->x2) {
      result ++;
      rev_friends_intersect_pos ++;
    }
  }
  if (T->x1 <= x1) {
    result += rev_friends_intersect (T->right, x1);
  }
  return result;
}