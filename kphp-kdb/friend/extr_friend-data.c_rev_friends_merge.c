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
struct TYPE_5__ {scalar_t__ y; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_1__ rev_friends_t ;

/* Variables and functions */

__attribute__((used)) static rev_friends_t *rev_friends_merge (rev_friends_t *L, rev_friends_t *R) {
  if (!L) { return R; }
  if (!R) { return L; }
  if (L->y > R->y) {
    L->right = rev_friends_merge (L->right, R);
    return L;
  } else {
    R->left = rev_friends_merge (L, R->left);
    return R;
  }
}