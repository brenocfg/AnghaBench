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
 size_t ba_admin ; 
 size_t ba_date ; 
 size_t ba_enemy ; 
 size_t ba_group_id ; 
 int /*<<< orphan*/  check_id (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int last_date ; 
 int /*<<< orphan*/  log_11_set (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_timestamp (int) ; 
 int /*<<< orphan*/  stderr ; 

void process_banlisted_row (void) {
  int group_id = I[ba_group_id];
  int enemy = I[ba_enemy];
  int admin = I[ba_admin];
  int date = I[ba_date]; 
  if (enemy <= 0 || group_id <= 0) {
    // fprintf (stderr, "skipping bogus entry (%d,%d,%d,%d)\n", owner, group_id, admin, date);
    return;
  }
  if (!check_id (enemy)) {
    return;
  }
  if (date != -1 && date < last_date - 10) {
    fprintf (stderr, "date goes back by %d seconds\n", last_date - date);
  } else if (date > last_date) {
    log_timestamp (date);
    last_date = date;
  }
  log_11_set (enemy, -group_id, admin, 0);
  adj_rec++;
}