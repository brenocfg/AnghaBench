#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_set_flags {int user_id; } ;

/* Variables and functions */
#define  LEV_CHANGE_FIELDMASK_DELAYED 134 
#define  LEV_CRC32 133 
#define  LEV_NOOP 132 
#define  LEV_ROTATE_FROM 131 
#define  LEV_ROTATE_TO 130 
#define  LEV_START 129 
#define  LEV_TIMESTAMP 128 
 int copy_mod ; 
 int copy_rem ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  targ_existed ; 

__attribute__((used)) static int want_write (int type, void *rec) {
  int user_id = 0;

  switch (type) {
  case LEV_START:
    return !targ_existed++ && !jump_log_pos;
  case LEV_NOOP:
    return 0;
  case LEV_TIMESTAMP:
  case LEV_CRC32:
  case LEV_ROTATE_TO:
  case LEV_ROTATE_FROM:
    return 0;
  case LEV_CHANGE_FIELDMASK_DELAYED:
    return 1;
  default:
    user_id = ((struct lev_set_flags *) rec)->user_id;
  }
  user_id %= copy_mod;
  if (user_id == copy_rem || user_id == -copy_rem) {
    return 1;
  }
  return 0;
}