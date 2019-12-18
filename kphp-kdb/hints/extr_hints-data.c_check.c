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
struct TYPE_3__ {int object_old_n; int /*<<< orphan*/  object_table; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ltbl_get_rev (int /*<<< orphan*/ *,int) ; 

inline void check (user *u, int local_id) {
  assert (local_id > 0);
  if (local_id > u->object_old_n) {
    assert (ltbl_get_rev (&u->object_table, local_id - u->object_old_n));
  }
}