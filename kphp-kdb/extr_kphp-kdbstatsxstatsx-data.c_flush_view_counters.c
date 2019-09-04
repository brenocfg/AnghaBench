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
struct lev_stats_views_ext64 {int views; int cnt_id; } ;
struct lev_stats_views_ext {int views; } ;
struct counter {int views_uncommitted; int counter_id; struct counter* commit_next; } ;

/* Variables and functions */
 scalar_t__ LEV_STATS_VIEWS ; 
 scalar_t__ LEV_STATS_VIEWS_64 ; 
 scalar_t__ LEV_STATS_VIEWS_EXT ; 
 scalar_t__ LEV_STATS_VIEWS_EXT_64 ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct counter* counters_commit_head ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int flush_view_counters (void) {
  struct counter *C = counters_commit_head, *D;
  int cnt = 0;
  if (verbosity > 1) {
    fprintf (stderr, "flush_view_counters()\n");
  }
  counters_commit_head = 0;
  while (C) {
    assert (++cnt <= 1000000);
    D = C->commit_next;
    C->commit_next = 0;
    assert (C->views_uncommitted > 0);
    if (C->counter_id == (int)C->counter_id) {
      struct lev_stats_views_ext *LV;
      if (C->views_uncommitted < 256) {
        LV = alloc_log_event (LEV_STATS_VIEWS + C->views_uncommitted, 8, C->counter_id);
      } else {
        LV = alloc_log_event (LEV_STATS_VIEWS_EXT, 12, C->counter_id);
        LV->views = C->views_uncommitted;
      }
    } else {
      struct lev_stats_views_ext64 *LV;
      if (C->views_uncommitted < 256) {
        LV = alloc_log_event (LEV_STATS_VIEWS_64 + C->views_uncommitted, 12, C->counter_id);
      } else {
        LV = alloc_log_event (LEV_STATS_VIEWS_EXT_64, 16, C->counter_id);
        LV->views = C->views_uncommitted;
      }
      LV->cnt_id = C->counter_id;
    }
    C->views_uncommitted = 0;
    C = D;
  }
  return cnt;
}