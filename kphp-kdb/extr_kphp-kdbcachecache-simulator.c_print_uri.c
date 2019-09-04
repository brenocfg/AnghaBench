#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int last_access; long long size; int /*<<< orphan*/ * hnext; } ;
struct TYPE_2__ {long long with_known_size_bytes; long long max_known_size; scalar_t__ max_uries_in_one_bucket; int /*<<< orphan*/  with_known_size_files; int /*<<< orphan*/  required_files_with_unknown_size; int /*<<< orphan*/  uries_last_month_access; int /*<<< orphan*/  uries_last_week_access; int /*<<< orphan*/  uries_last_day_access; int /*<<< orphan*/  uries_last_hour_access; } ;

/* Variables and functions */
 char* cache_get_uri_name (struct cache_uri*) ; 
 int now ; 
 scalar_t__ print_unknown_size_uries ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__ simulation_stats ; 
 scalar_t__ uri_in_bucket ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

void print_uri (struct cache_uri *U) {
  if (U->last_access > now) {
    vkprintf (1, "U->last_access: %d, now: %d\n", U->last_access, now);
  }
  if (U->last_access >= now - 3600) {
    simulation_stats.uries_last_hour_access++;
  }
  if (U->last_access >= now - 86400) {
    simulation_stats.uries_last_day_access++;
  }
  if (U->last_access >= now - 86400 * 7) {
    simulation_stats.uries_last_week_access++;
  }
  if (U->last_access >= now - 86400 * 30) {
    simulation_stats.uries_last_month_access++;
  }

  if (U->size == -2LL) {
    simulation_stats.required_files_with_unknown_size++;
    if (print_unknown_size_uries) {
      printf ("%s\n", cache_get_uri_name (U));
    }
  } else if (U->size >= 0) {
    simulation_stats.with_known_size_files++;
    simulation_stats.with_known_size_bytes += U->size;
    if (simulation_stats.max_known_size < U->size) {
      simulation_stats.max_known_size = U->size;
    }
  }
  uri_in_bucket++;
  if (U->hnext == NULL) {
    if (simulation_stats.max_uries_in_one_bucket < uri_in_bucket) {
      simulation_stats.max_uries_in_one_bucket = uri_in_bucket;
    }
    uri_in_bucket = 0;
  }
}