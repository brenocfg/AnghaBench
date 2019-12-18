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
struct TYPE_3__ {int object_old_n; long long* object_type_ids; int /*<<< orphan*/  object_table; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int ltbl_get_to (int /*<<< orphan*/ *,long long) ; 

int user_get_object_local_id_type_id (user *u, long long type_id) {
  if (u->object_old_n) {
    int l = 1, r = u->object_old_n + 1, c;
    while (l + 1 < r) {
      c = (l + r) >> 1;
      if (u->object_type_ids[c] <= type_id) {
        l = c;
      } else {
        r = c;
      }
    }

    if (u->object_type_ids[l] == type_id) {
      return l;
    }
  }

  int res = ltbl_get_to (&u->object_table, type_id);
  if (res == 0) {
    return 0;
  }
  return res + u->object_old_n;
}