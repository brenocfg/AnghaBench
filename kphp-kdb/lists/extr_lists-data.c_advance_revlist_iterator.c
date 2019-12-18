#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int eof; scalar_t__ cur_pos; scalar_t__ items_num; scalar_t__ metafile_number; scalar_t__ change_metafile; } ;

/* Variables and functions */
 int init_revlist_iterator (scalar_t__,scalar_t__) ; 
 TYPE_1__ revlist_iterator ; 
 scalar_t__ revlist_metafile_mode ; 
 int /*<<< orphan*/  update_revlist_use (scalar_t__) ; 

int advance_revlist_iterator (void) {
  if (revlist_iterator.eof) {
    return 0;
  }
  revlist_iterator.cur_pos ++;
  if (revlist_iterator.cur_pos == revlist_iterator.items_num) {
    if (!revlist_iterator.change_metafile) {
      revlist_iterator.eof = 1;
      return 0;
    } else {
      return init_revlist_iterator (revlist_iterator.metafile_number + 1, revlist_iterator.change_metafile);
    }
  } else {
    if (revlist_metafile_mode && revlist_iterator.change_metafile) {
      update_revlist_use (revlist_iterator.metafile_number);
    }
    return 1;
  }
}