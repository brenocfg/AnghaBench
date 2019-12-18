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
struct TYPE_3__ {int /*<<< orphan*/  fr_tree; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int R ; 
 int R_cat_mask ; 
 int R_end ; 
 int R_mode ; 
 scalar_t__ conv_uid (int) ; 
 TYPE_1__* get_user (int) ; 
 int /*<<< orphan*/  tree_fetch (int /*<<< orphan*/ ) ; 

int prepare_friends (int user_id, int cat_mask, int mode) {
  user_t *U = get_user (user_id);
  if ((!U && conv_uid (user_id) < 0) || mode < 0 || mode > 2) {
    return -1;
  }
  R_end = R;
  if (!U) {
    return 0;
  }
  R_cat_mask = cat_mask;
  R_mode = mode;
  tree_fetch (U->fr_tree);
  return (R_end - R) / (mode + 1);
}