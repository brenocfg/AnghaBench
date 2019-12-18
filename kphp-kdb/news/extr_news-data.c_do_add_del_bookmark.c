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

/* Variables and functions */
 int /*<<< orphan*/  PACK_BOOKMARK (long long,int,int,int) ; 
 int /*<<< orphan*/  UNPACK_BOOKMARK (long long,int,int,int) ; 
 int add_del_bookmark (int,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int /*<<< orphan*/  insert_bookmark (int,long long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_bookmark_log (int,int,int,int,int) ; 

int do_add_del_bookmark (int user_id, int type, int owner, int place, int y) {
  //fprintf (stderr, "%d (%d, %d) - (%d, %d) %d\n", type, owner, place, log_split_min, log_split_mod, user_id);
  if (!check_obj (type, owner, place) || user_id <= 0) {
    return 0;
  }
  long long t;
  PACK_BOOKMARK (t, type, owner, place);
  int x, yy, z;
  UNPACK_BOOKMARK (t, x, yy, z);
  //fprintf (stderr, "%x(%x) %x(%x) %x(%x) %llx\n", type, x, owner, yy, place, z, t);
  assert (x == type && yy == owner && z == place);
  if (!insert_bookmark (user_id, t, y, 0)) {
    insert_bookmark_log (user_id, type, owner, place, y);
    return add_del_bookmark (user_id, type, owner, place, y);
  }
  return 1;
}