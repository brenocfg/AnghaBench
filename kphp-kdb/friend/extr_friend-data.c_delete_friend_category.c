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
struct TYPE_3__ {int* cat_ver; int cat_mask; int /*<<< orphan*/  fr_tree; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  tree_clean_cat (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int delete_friend_category (user_t *U, int cat, int op) {
  if (!U || cat <= 0 || cat >= 32) {
    return -1;
  }
  tree_clean_cat (U->fr_tree, ~(1 << cat));
  if (op) {
    U->cat_ver[cat] += 0x100;
    U->cat_mask &= ~(1 << cat);
  }
  return 1;
}