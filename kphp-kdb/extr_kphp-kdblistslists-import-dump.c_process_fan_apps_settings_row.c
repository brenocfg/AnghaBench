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
 void** I ; 
 scalar_t__ LEV_LI_DECR_FLAGS ; 
 scalar_t__ LEV_LI_INCR_FLAGS ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t as_app_id ; 
 int as_can_access_audio ; 
 size_t as_can_notify ; 
 size_t as_user_id ; 
 scalar_t__ conv_uid (void*) ; 
 void* list_id ; 
 int /*<<< orphan*/  log_1int (scalar_t__,int) ; 

void process_fan_apps_settings_row (void) {
  int app_id = I[as_app_id], flags = 0, i;
  list_id = I[as_user_id];
  if (conv_uid (list_id) < 0 || app_id <= 0) {
    return;
  }
  for (i = as_can_notify; i <= as_can_access_audio; i++) {
    if (I[i]) {
      flags += (1 << i);
    }
  }
  if (!I[as_can_notify]) {
    log_1int (LEV_LI_DECR_FLAGS + (1 << as_can_notify), app_id);
  }
  log_1int (LEV_LI_INCR_FLAGS + flags, app_id);
  adj_rec++;
}