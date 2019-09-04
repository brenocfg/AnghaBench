#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int history_ts; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 scalar_t__ conv_uid (int) ; 
 TYPE_1__* get_user (int) ; 
 TYPE_1__* get_user_f (int) ; 
 int new_history_ts () ; 

int get_timestamp (int user_id, int force) {
  user_t *U;

  if (conv_uid (user_id) < 0) {
    return -1;
  }

  if (force) {
    U = get_user_f (user_id);
    if (!U->history_ts) {
      U->history_ts = new_history_ts ();
    }
  } else {
    U = get_user (user_id);
    if (!U || !U->history_ts) {
      return 0;
    }
  }

  return U->history_ts;
}