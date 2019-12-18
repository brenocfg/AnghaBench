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
 int* I ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t bl_enemy ; 
 size_t bl_owner ; 
 int /*<<< orphan*/  check_id (int) ; 
 int /*<<< orphan*/  log_11_set (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void process_blacklisted_row (void) {
  int owner = I[bl_owner];
  int enemy = I[bl_enemy];
  if (enemy <= 0 || owner <= 0) {
    // fprintf (stderr, "skipping bogus entry (%d,%d,%d,%d)\n", owner, enemy, admin, date);
    return;
  }
  if (!check_id (enemy)) {
    return;
  }
  log_11_set (enemy, owner, 0, 0);
  adj_rec++;
}