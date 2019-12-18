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
struct lev_cache_uri {int /*<<< orphan*/  data; } ;
struct cache_uri {scalar_t__ last_access; } ;

/* Variables and functions */
 int CACHE_FEATURE_REPLAY_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int cache_features_mask ; 
 int /*<<< orphan*/  cache_uri_free (struct cache_uri*) ; 
 struct cache_uri* get_uri_f (char*,int) ; 
 scalar_t__ log_last_ts ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uri_living_time ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*,...) ; 

__attribute__((used)) static void cache_uri_delete (struct lev_cache_uri *E, int l) {
  assert (log_last_ts > 0);
  if (cache_features_mask & CACHE_FEATURE_REPLAY_DELETE) {
    char uri[256];
    memcpy (uri, E->data, l);
    uri[l] = 0;
    struct cache_uri *U = get_uri_f (uri, 0);
    if (U == NULL) {
      vkprintf (2, "Delete not existing global uri - \"%s\".\n", uri);
      return;
    }
    if (U->last_access >= log_last_ts - uri_living_time + 7200) {
      vkprintf (2, "Skip deleting global uri, since it isn't too old - \"%s\", log_last_ts: %d, last_access: %d\n", uri, log_last_ts, U->last_access);
      return;
    }
    assert (U == get_uri_f (uri, -1));
    cache_uri_free (U);
  }
}