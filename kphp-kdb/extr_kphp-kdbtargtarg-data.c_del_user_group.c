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
struct TYPE_3__ {int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_user_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  field_value_hash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q_grp_id ; 
 int /*<<< orphan*/  user_group_pairs ; 

__attribute__((used)) static int del_user_group (user_t *U, int group_id) {
  delete_user_word (U->uid, field_value_hash (q_grp_id, group_id));
  user_group_pairs--;

  return 1;
}