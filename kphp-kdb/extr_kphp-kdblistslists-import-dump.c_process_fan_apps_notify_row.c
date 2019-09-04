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
 scalar_t__ LEV_LI_ADD_ENTRY ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t an_app_id ; 
 size_t an_inviter_id ; 
 size_t an_user_id ; 
 scalar_t__ conv_uid (void*) ; 
 void* list_id ; 
 int /*<<< orphan*/  log_2ints (scalar_t__,int,void*) ; 

void process_fan_apps_notify_row (void) {
  int app_id = I[an_app_id];
  list_id = I[an_user_id];
  if (conv_uid (list_id) < 0 || list_id <= 0 || app_id <= 0) {
    return;
  }
  log_2ints (LEV_LI_ADD_ENTRY + 2, app_id, I[an_inviter_id]);
  adj_rec++;
}