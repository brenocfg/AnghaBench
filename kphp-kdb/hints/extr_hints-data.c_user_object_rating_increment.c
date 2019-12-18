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
struct TYPE_3__ {int /*<<< orphan*/  chg_list_en; int /*<<< orphan*/  chg_list_st; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  changes_count ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_rating (int) ; 
 int /*<<< orphan*/  check_rating_num (int) ; 
 int /*<<< orphan*/  chg_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char,int,int) ; 
 scalar_t__ no_changes ; 
 scalar_t__ write_only ; 

int user_object_rating_increment (user *u, unsigned char object_type, long long object_id, int cnt, int num) {
  if (!check_rating (cnt) || object_type == 0 || !check_object_id (object_id) || !check_rating_num (num)) {
    return 0;
  }

  if (write_only || no_changes) {
    return 1;
  }

  chg_list_add_int (&u->chg_list_st, &u->chg_list_en, +(object_type + 256 * num), -(int)(object_id), cnt);
  changes_count++;

  return 1;
}