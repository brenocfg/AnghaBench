#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lev_cache_uri {int /*<<< orphan*/  data; } ;
struct cache_uri {char* local_copy; } ;
struct TYPE_4__ {scalar_t__ disk_size; } ;
struct TYPE_3__ {long long cache_init_bytes; int /*<<< orphan*/  cache_init_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct cache_uri*) ; 
 long long cache_get_uri_size (struct cache_uri*,int) ; 
 scalar_t__ cached_bytes ; 
 struct cache_uri* get_uri_f (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ simulation_params ; 
 TYPE_1__ simulation_stats ; 

void greedy_init_uri_add (struct lev_cache_uri *E, int l) {
  char uri[256];
  memcpy (uri, E->data, l);
  uri[l] = 0;
  struct cache_uri *U = get_uri_f (uri, 0);
  assert (U);
  if (U->local_copy == NULL) {
    long long s = cache_get_uri_size (U, 1);
    if (cached_bytes + s <= simulation_params.disk_size) {
      U->local_copy = "cached";
      cached_bytes += s;
      simulation_stats.cache_init_files++;
      simulation_stats.cache_init_bytes += s;
    }
  }
}