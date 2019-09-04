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
struct data {int data_len; char* data; int flags; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_get ; 
 int /*<<< orphan*/  disable_wildcard ; 
 struct data do_pmemcached_get (char const*,int) ; 
 int do_pmemcached_preload (char const*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  get_hits ; 
 int /*<<< orphan*/  get_missed ; 
 int memcache_get_wildcard (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  memcache_wait (struct connection*) ; 
 scalar_t__ pmemcache_match_stats_key (char const*,int) ; 
 int pmemcache_prepare_stats (struct connection*) ; 
 scalar_t__ protected_mode ; 
 scalar_t__ return_false_if_not_found ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_one_key_flags (struct connection*,char const*,char*,int,int) ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (verbosity >= 3) {
    fprintf (stderr, "memcache_get: key='%s'\n", key);
  }
  if (pmemcache_match_stats_key (key, key_len)) {
    int stats_len = pmemcache_prepare_stats (c);
    return_one_key (c, key, stats_buff, stats_len);
    return 0;
  }
  if (protected_mode) { return 0; }

  cmd_get++;
  if (!disable_wildcard && (key[key_len - 1] == '*' || key[key_len - 1] == '#')) {
    return memcache_get_wildcard (c, key, key_len);
  }

  if (do_pmemcached_preload (key, key_len, 1) == -2) {
    memcache_wait (c);
    return 0;
  }

  struct data x = do_pmemcached_get (key, key_len);

  if (x.data_len >= 0) {
    get_hits++;
    return_one_key_flags (c, key, x.data, x.data_len, x.flags);
  } else {
    if (x.data_len == -1 || x.data_len == -2) { // -2 can be returned if key is deleted by time and key was not in index
      if (return_false_if_not_found) {
        return_one_key_flags (c, key, "b:0;", 4, 1);
      }
      get_missed++;
    } else {
      assert (0);
    }
  }

  return 0;
}