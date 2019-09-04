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
struct TYPE_4__ {scalar_t__ value; scalar_t__ y; size_t next; } ;
struct TYPE_3__ {size_t new_pos; scalar_t__* old_pos; scalar_t__* last_old_pos; scalar_t__ value; } ;

/* Variables and functions */
 size_t NIL_BOOKMARK ; 
 TYPE_2__* bookmarks ; 
 TYPE_1__ iterator ; 

int advance_iterator (void) {
  #define new_end (iterator.new_pos == NIL_BOOKMARK)
  #define old_end (iterator.old_pos == iterator.last_old_pos)
  #define new_value (bookmarks[iterator.new_pos].value)
  #define old_value (*iterator.old_pos)
  #define new_adv (iterator.new_pos = bookmarks[iterator.new_pos].next)
  #define old_adv (iterator.old_pos ++)
  #define new_y (bookmarks[iterator.new_pos].y)
  while (1) {
    if (new_end && old_end) {
      return -1;
    } else {
      if (new_end || (!old_end && old_value < new_value)) {
        iterator.value = old_value;
        old_adv;
        return 0;
      } else if (old_end || (!new_end && new_value < old_value)) {
        if (new_y > 0) {
          iterator.value = new_value;
          new_adv;
          return 0;
        } else {
          new_adv;
        }
      } else {
        if (new_y > 0) {
          iterator.value = new_value;
          old_adv;
          new_adv;
          return 0;
        } else {
          old_adv;
          new_adv;
        }
      }
    }
  }
  #undef new_end
  #undef old_end
  #undef new_value
  #undef old_value
  #undef new_adv
  #undef old_adv
  #undef new_y
}