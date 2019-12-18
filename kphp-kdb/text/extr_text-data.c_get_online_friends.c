#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  online_tree; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int R ; 
 int RA ; 
 int R_cnt ; 
 int /*<<< orphan*/  adjust_online_tree (TYPE_1__*) ; 
 scalar_t__ conv_uid (int) ; 
 int /*<<< orphan*/  fetch_online_tree (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* get_user (int) ; 
 int /*<<< orphan*/  sort_res (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sort_res2 (int /*<<< orphan*/ ,int) ; 

int get_online_friends (int user_id, int mode) {
  user_t *U = get_user (user_id);
  R_cnt = 0;
  if (!U) {
    return conv_uid (user_id) < 0 ? -1 : 0;
  }
  RA = R;
  adjust_online_tree (U);
  fetch_online_tree (U->online_tree, mode);
  R_cnt = RA - R;
  if (mode) {
    sort_res2 (0, (R_cnt >> 1) - 1);
    return R_cnt >> 1;
  } else {
    sort_res (0, R_cnt - 1);
    return R_cnt;
  }
}