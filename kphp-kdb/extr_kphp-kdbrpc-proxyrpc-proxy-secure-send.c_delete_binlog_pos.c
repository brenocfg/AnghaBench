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
struct binlog_pos {long long pos; scalar_t__ timestamp; scalar_t__ crc32; } ;
struct tree_binlog_pos {struct binlog_pos x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct tree_binlog_pos*) ; 
 int /*<<< orphan*/  binlog_pos_tree ; 
 struct binlog_pos get_cur_binlog_position (int) ; 
 int /*<<< orphan*/  tree_delete_binlog_pos (int /*<<< orphan*/ ,struct binlog_pos) ; 
 struct tree_binlog_pos* tree_get_min_binlog_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_index (long long,scalar_t__,scalar_t__) ; 

void delete_binlog_pos (long long pos, int binlog_replay) {
  struct binlog_pos t;
  t.pos = pos;
  t.crc32 = 0;
  t.timestamp = 0;
  binlog_pos_tree = tree_delete_binlog_pos (binlog_pos_tree, t);
  if (!binlog_pos_tree) {
    t = get_cur_binlog_position (binlog_replay);
  } else {
    struct tree_binlog_pos *T = tree_get_min_binlog_pos (binlog_pos_tree);
    assert (T);
    t = T->x;
  }
  update_index (t.pos, t.crc32, t.timestamp);
}