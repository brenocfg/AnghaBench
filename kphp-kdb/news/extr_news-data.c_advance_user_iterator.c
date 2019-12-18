#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int user_id; } ;
struct TYPE_7__ {int user_id; } ;
struct TYPE_6__ {int user_id; } ;
struct TYPE_5__ {size_t new_pos; size_t small_pos; size_t large_pos; int value; } ;

/* Variables and functions */
 int MAXINT ; 
 TYPE_4__* large_users ; 
 size_t large_users_number ; 
 int min (int,int) ; 
 TYPE_3__* new_users ; 
 size_t new_users_number ; 
 TYPE_2__* small_users ; 
 size_t small_users_number ; 
 TYPE_1__ user_iterator ; 

int advance_user_iterator (void) {
  int new_value = user_iterator.new_pos < new_users_number ? new_users[user_iterator.new_pos].user_id : MAXINT;
  int small_value = user_iterator.small_pos < small_users_number ? small_users[user_iterator.small_pos].user_id : MAXINT;
  int large_value = user_iterator.large_pos < large_users_number ? large_users[user_iterator.large_pos].user_id : MAXINT;
  int mi = min (new_value, min (small_value, large_value));
  if (mi == MAXINT) {
    return -1;
  }
  user_iterator.value = mi;
  if (new_value == mi) {
    user_iterator.new_pos++;
  }
  if (small_value == mi) {
    user_iterator.small_pos++;
  }
  if (large_value == mi) {
    user_iterator.large_pos++;
  }
  return 1;
}