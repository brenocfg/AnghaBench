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
union cache_packed_local_copy_location {int /*<<< orphan*/  i; } ;
struct lev_cache_set_new_local_copy_short {int /*<<< orphan*/  data; } ;
struct lev_cache_set_new_local_copy_long {int /*<<< orphan*/  data; int /*<<< orphan*/  md5; } ;
struct cache_uri {char const uri_md5_h0; } ;
struct cache_local_copy {int /*<<< orphan*/  packed_location; int /*<<< orphan*/  location; scalar_t__ flags; } ;
struct TYPE_3__ {char const* const c; } ;
struct TYPE_4__ {TYPE_1__ uri_md5; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MAX_LOCAL_COPIES ; 
 struct cache_local_copy* LC ; 
 scalar_t__ LEV_CACHE_SET_NEW_LOCAL_COPY_LONG ; 
 scalar_t__ LEV_CACHE_SET_NEW_LOCAL_COPY_SHORT ; 
 void* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cache_get_unique_md5_bytes (struct cache_uri*) ; 
 int /*<<< orphan*/  cache_local_copy_compute_packed_location (struct cache_local_copy*,union cache_packed_local_copy_location*) ; 
 int /*<<< orphan*/  cache_local_copy_init (struct cache_local_copy*) ; 
 int /*<<< orphan*/  cache_local_copy_try_pack_location (struct cache_uri*,struct cache_local_copy*) ; 
 int cache_local_copy_unpack (struct cache_uri*,struct cache_local_copy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cache_uri_incr_monthly_stats (struct cache_uri*,struct cache_local_copy*) ; 
 int /*<<< orphan*/  cache_uri_incr_server_stats0 (struct cache_uri*,union cache_packed_local_copy_location) ; 
 int /*<<< orphan*/  cache_uri_update_local_copy (struct cache_uri*,struct cache_local_copy*,int,int) ; 
 int /*<<< orphan*/  compute_get_uri_f_last_md5 (struct cache_uri*) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 
 TYPE_2__ get_uri_f_last_md5 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const* const,int const) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const* const) ; 
 int strlen (char const* const) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const* const,...) ; 

int cache_do_set_new_local_copy (const char *const global_uri, const char *const local_uri) {
  vkprintf (3, "cache_do_set_new_local_copy (%s, %s)\n", global_uri, local_uri);
  struct cache_uri *U = get_uri_f (global_uri, 0);
  if (U == NULL) {
    return -1;
  }
  LC[0].flags = 0;
  strcpy (LC[0].location, local_uri);
  union cache_packed_local_copy_location u;
  cache_local_copy_compute_packed_location (LC, &u);
  if (!u.i) {
    vkprintf (2, "Couldn't compute ${node_id},${server_id},${disk_id} for local uri: %s\n", local_uri);
    return -1;
  }
  int i, n, old_len;
  n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 1, &old_len);
  if (n < 0) {
    return -1;
  }
  for (i = 0; i < n; i++) {
    if (!strcmp (LC[i].location, local_uri)) {
      vkprintf (2, "cache_do_set_new_local_copy (global_uri: %s, local_uri: %s): ignore duplicate set.\n", global_uri, local_uri);
      return -1;
    }
  }
  struct cache_local_copy *L = &LC[n++];
  cache_local_copy_init (L);
  const int l = strlen (local_uri);
  assert (l < 256);
  strcpy (L->location, local_uri);

  const int bytes = cache_get_unique_md5_bytes (U);
  assert (bytes != 0);
  if (!cache_local_copy_try_pack_location (U, L) && bytes == 8) {
    struct lev_cache_set_new_local_copy_short *E = alloc_log_event (LEV_CACHE_SET_NEW_LOCAL_COPY_SHORT, sizeof (*E), L->packed_location);
    memcpy (E->data, &U->uri_md5_h0, 8);
  } else {
    struct lev_cache_set_new_local_copy_long *E = alloc_log_event (LEV_CACHE_SET_NEW_LOCAL_COPY_LONG + l, sizeof (*E) + l, 0);
    compute_get_uri_f_last_md5 (U);
    memcpy (E->md5, get_uri_f_last_md5.uri_md5.c, 16);
    memcpy (E->data, local_uri, l);
  }

#ifdef CACHE_FEATURE_MONTHLY_COUNTER_PERF_STATS
  cache_uri_incr_monthly_stats (U, L);
#endif
  cache_uri_incr_server_stats0 (U, u);
  cache_uri_update_local_copy (U, LC, n, old_len);
  return 0;
}