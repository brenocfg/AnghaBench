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
struct lev_del_list {int* list_id; } ;

/* Variables and functions */
#define  LEV_CRC32 136 
#define  LEV_LI_DEL_OBJ 135 
#define  LEV_NOOP 134 
#define  LEV_ROTATE_FROM 133 
#define  LEV_ROTATE_TO 132 
#define  LEV_START 131 
#define  LEV_TIMESTAMP 130 
#define  SPLIT_FIRSTINT 129 
#define  SPLIT_LIKED 128 
 int abs (int) ; 
 int copy_mod ; 
 int copy_rem ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  split_mode ; 
 int /*<<< orphan*/  targ_existed ; 

__attribute__((used)) static int default_want_write (int type, void *rec, int size) {
  int list_id = 0;
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
  case LEV_LI_DEL_OBJ:
    return 1;
  default: {
    switch (split_mode) {
    case SPLIT_FIRSTINT:
      list_id = ((struct lev_del_list *) rec)->list_id[0];
      break;
    case SPLIT_LIKED:
      list_id = abs(((struct lev_del_list *) rec)->list_id[0]) + abs(((struct lev_del_list *) rec)->list_id[1]);
      break;
    }
  }
  }
  list_id %= copy_mod;
  if (list_id == copy_rem || list_id == -copy_rem) {
    return 1;
  }
  return 0;
}