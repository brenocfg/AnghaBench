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
 int immediate_mode ; 
 int load_user_metafile (int /*<<< orphan*/ *,int,int) ; 
 int local_user_id (int) ; 
 TYPE_2__ user_table ; 
 int /*<<< orphan*/ * users ; 

user *conv_user_id (int user_id) {
  int local_id = local_user_id (user_id);
  if (local_id == -1) {
    return NULL;
  }

  assert (local_id + 1 < user_table.to.size);

  user *u = &users[local_id];

  if (immediate_mode == 1) {
    assert (load_user_metafile (u, local_id, 1));
  }

  return u;
}