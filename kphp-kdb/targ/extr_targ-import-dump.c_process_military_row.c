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
struct lev_military {void* finish; void* start; void* unit_id; void* user_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void** I ; 
 int /*<<< orphan*/  LEV_TARG_MIL_ADD ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (void*) ; 
 size_t mi_finished ; 
 size_t mi_member_id ; 
 size_t mi_started ; 
 size_t mi_unit_id ; 
 void* user_id ; 
 struct lev_military* write_alloc (int) ; 

void process_military_row (void) {
  struct lev_military *E;
  user_id = I[mi_member_id];

  if (!fits(user_id)) {
    return;
  }

  E = write_alloc (sizeof (*E));
  E->type = LEV_TARG_MIL_ADD;
  E->user_id = I[mi_member_id];
  E->unit_id = I[mi_unit_id];
  E->start = I[mi_started];
  E->finish = I[mi_finished];

  adj_rec++;

}