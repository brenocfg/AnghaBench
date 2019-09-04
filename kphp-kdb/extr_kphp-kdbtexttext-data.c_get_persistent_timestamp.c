#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int persistent_ts; TYPE_1__* persistent_history; } ;
typedef  TYPE_2__ user_t ;
struct file_user_list_entry_search_history {int user_history_max_ts; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_events; } ;

/* Variables and functions */
 scalar_t__ conv_uid (int) ; 
 TYPE_2__* get_user (int) ; 
 scalar_t__ lookup_user_directory (int) ; 
 int /*<<< orphan*/  persistent_history_enabled ; 

int get_persistent_timestamp (int user_id) {
  if (!persistent_history_enabled || conv_uid (user_id) < 0) {
    return -1;
  }

  user_t *U = get_user (user_id);

  if (!U) {
    struct file_user_list_entry_search_history *D = (struct file_user_list_entry_search_history *) lookup_user_directory (user_id);
    return D ? D->user_history_max_ts + 1 : 1;
  }
  return U->persistent_ts + 1 + (U->persistent_history ? U->persistent_history->cur_events : 0);
}