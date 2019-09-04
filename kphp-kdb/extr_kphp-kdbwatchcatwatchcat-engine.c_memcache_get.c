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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT ; 
 scalar_t__ MAX_VALUE_LEN ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  get ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int my_verbosity_tmp ; 
 int prepare_stats (struct connection*,char*,scalar_t__) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char*,char*,int) ; 
 int sscanf (char*,char*,long long*,int*,int*,int*) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  subscribe_watchcat (long long,char*,int,int) ; 
 int watchcat_prepare_stats () ; 

int memcache_get (struct connection *c, const char *old_key, int old_key_len) {
  INIT;

  if (my_verbosity_tmp > 1) {
    fprintf (stderr, "memcache_get: key='%s'\n", old_key);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = watchcat_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, MAX_VALUE_LEN - len);
    return_one_key (c, key, stats_buff, len + len2 - 1);

    return 0;
  }

  if (key_len >= 15 && !strncmp (key, "create_watchcat", 15) ) {
    int len;
    long long id;
    int timeout, q_id;

    if (sscanf (key + 15, "%lld,%d,%d%n", &id, &timeout, &q_id, &len) == 3 && key[len += 15] == '(' && key[key_len - 1] == ')') {
      char *s = stats_buff;
      int n = key_len - len - 2;
      memcpy (s, key + len + 1, n);
      s[n] = 0;

      subscribe_watchcat (id, s, q_id, timeout);
    }
  }

  RETURN(get, 0);
}