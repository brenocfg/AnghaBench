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
 int* I ; 
 int MAX_GROUPS ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t gs_id ; 
 size_t gs_is_event ; 

void process_groups_short_row (void) {
  int group_id = I[gs_id];
  int is_event = I[gs_is_event];
  if (group_id <= 0 || group_id >= MAX_GROUPS || (is_event & -2)) {
    return;
  }
  if (Gc <= group_id) {
    Gc = group_id + 1;
  }
  GT[group_id] = 2+is_event;
  adj_rec++;
}