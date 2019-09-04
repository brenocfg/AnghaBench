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
struct TYPE_4__ {int object_old_n; int /*<<< orphan*/ * object_ratings; int /*<<< orphan*/ * object_old_ratings; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  rating ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check (TYPE_1__*,int) ; 
 int rating_num ; 

rating *user_get_object_rating (user *u, int local_id, int num) {
  check (u, local_id);
  assert (0 <= num && num < rating_num);

  if (local_id <= u->object_old_n) {
    return &u->object_old_ratings[local_id * rating_num + num];
  } else {
    return &u->object_ratings[(local_id - u->object_old_n) * rating_num + num];
  }
}