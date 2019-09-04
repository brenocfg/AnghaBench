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
struct counter {long long counter_id; int created_at; int last_month_unique_visitors; int long_unique_visitors; int last_week_unique_visitors; int valid_until; int /*<<< orphan*/  type; struct counter* prev; int /*<<< orphan*/  timezone; } ;

/* Variables and functions */
 scalar_t__ FORCE_COUNTER_TYPE ; 
 scalar_t__ auto_create_new_versions ; 
 int /*<<< orphan*/  copy_ancestor (struct counter*,struct counter*) ; 
 scalar_t__ create_day_start ; 
 scalar_t__ custom_version_names ; 
 int /*<<< orphan*/  default_timezone ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_cnt_type (long long) ; 
 int incr_version ; 
 int now ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_counters_allocated ; 
 int tz_offset (int /*<<< orphan*/ ) ; 
 int verbosity ; 
 struct counter* zzmalloc0 (int) ; 

__attribute__((used)) static struct counter *malloc_counter (struct counter *D, long long cnt_id) {
  if (verbosity >= 4) {
    fprintf (stderr, "Allocating new counter\n");
  }
  struct counter *C = zzmalloc0 (sizeof (struct counter));
  if (!C) return C;
  tot_counters_allocated++;
  C->counter_id = cnt_id;
  C->prev = 0;
  C->timezone = default_timezone;
  if (D) {
    copy_ancestor (C, D);
  }
  if (create_day_start) {
    C->created_at = now - (now + tz_offset (C->timezone)) % 86400;
  } else {
    C->created_at = now;
  }
  C->last_month_unique_visitors = -1;
  C->long_unique_visitors = -1;
  C->last_week_unique_visitors = -1;
  if (auto_create_new_versions) {
    C->valid_until = now - (now + tz_offset (C->timezone)) % 86400 + 86400;
  } else {
    C->valid_until = 0x7fffffff;
  }
  if (custom_version_names) {
    C->created_at = incr_version;
  }
  C->prev = D;
  if (!D || FORCE_COUNTER_TYPE) {
    C->type = get_cnt_type (cnt_id);
  }
  if (verbosity >= 4) {
    fprintf (stderr, "New counter allocated\n");
  }
  return C;
}