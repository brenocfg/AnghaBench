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
 int* GT ; 
 int Gc ; 
 void** I ; 
 scalar_t__ LEV_LI_SET_ENTRY ; 
 int /*<<< orphan*/  adj_rec ; 
 scalar_t__ conv_uid (void*) ; 
 void* list_id ; 
 int /*<<< orphan*/  log_2ints (scalar_t__,int,int) ; 
 size_t mg_confirmed ; 
 size_t mg_group_id ; 
 size_t mg_user_id ; 
 size_t mg_who_invited ; 

void process_member_groups_row (void) {
  int group_id = I[mg_group_id];
  int confirmed = I[mg_confirmed];
  int who_invited = I[mg_who_invited];
  list_id = I[mg_user_id];
  if (conv_uid (list_id) < 0 || list_id <= 0 || group_id <= 0 || confirmed <= 0 || confirmed > 2) {
    return;
  }
  if (group_id < Gc) {
    if (GT[group_id] == 3) {
      confirmed += 4;
    } else if (GT[group_id] != 2) {
      return;
    }
  }
  log_2ints (LEV_LI_SET_ENTRY + confirmed + 1, group_id, who_invited > 0 ? who_invited : 0);
  adj_rec++;
}