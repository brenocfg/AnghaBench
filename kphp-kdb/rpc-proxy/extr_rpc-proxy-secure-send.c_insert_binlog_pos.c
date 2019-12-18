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
struct binlog_pos {long long pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_pos_tree ; 
 struct binlog_pos get_cur_binlog_position (int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  tree_insert_binlog_pos (int /*<<< orphan*/ ,struct binlog_pos,int /*<<< orphan*/ ) ; 

void insert_binlog_pos (long long pos, int binlog_replay) {
  struct binlog_pos t;
  t = get_cur_binlog_position (binlog_replay);
  assert (t.pos == pos);
  binlog_pos_tree = tree_insert_binlog_pos (binlog_pos_tree, t, lrand48 ());
}