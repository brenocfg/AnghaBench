#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
struct TYPE_3__ {int size; } ;
struct TYPE_4__ {TYPE_1__ to; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int local_uid (int) ; 
 TYPE_2__ user_table ; 
 int /*<<< orphan*/ * users ; 

user *conv_uid (int user_id) {
  int local_id = local_uid (user_id);
  if (local_id == -1) {
    return NULL;
  }

  assert (local_id < user_table.to.size);
  return &users[local_id];
}