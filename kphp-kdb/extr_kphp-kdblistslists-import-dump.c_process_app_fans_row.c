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
 scalar_t__ LEV_LI_SET_ENTRY ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t af_app_id ; 
 size_t af_user_id ; 
 scalar_t__ conv_uid (void*) ; 
 void* list_id ; 
 int /*<<< orphan*/  log_2ints (scalar_t__,int,int /*<<< orphan*/ ) ; 

void process_app_fans_row (void) {
  int user_id = I[af_user_id];
  list_id = I[af_app_id];
  if (conv_uid (list_id) < 0 || !user_id) {
    return;
  }
  log_2ints (LEV_LI_SET_ENTRY + (user_id < 0 ? 23 : 19), user_id, 0);
  adj_rec++;
}