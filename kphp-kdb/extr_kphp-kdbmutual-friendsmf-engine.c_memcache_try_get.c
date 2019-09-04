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
 int MAX_CNT ; 
 int MAX_FRIENDS ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int STATS_BUFF_SIZE ; 
 int active_aio_queries ; 
 int /*<<< orphan*/  assert (int) ; 
 char* buf ; 
 int /*<<< orphan*/  do_add_exception (int,int) ; 
 int do_clear_exceptions (int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int* fr_buff ; 
 int /*<<< orphan*/  get ; 
 int get_suggestions (int,int,int,int*) ; 
 int mf_prepare_stats () ; 
 int prepare_stats (struct connection*,char*,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int sscanf (char*,char*,int*,...) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_try_get (struct connection *c, const char *old_key, int old_key_len) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 11 && !strncmp (key, "unload_user", 11)) {
    int uid;

    sscanf (key, "unload_user%d", &uid);
//    test_user_unload (uid);

    return_one_key (c, old_key, "0", 1);

    RETURN(get, 0);
  }

  if (key_len >= 10 && !strncmp (key, "unload_lru", 10)) {
//    user_LRU_unload();
    return_one_key (c, old_key, "0", 1);

    RETURN(get, 0);
  }


  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = mf_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    assert (len + len2 + 1 < STATS_BUFF_SIZE);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }


  if (key_len >= 9 && !strncmp (key, "exception", 9)) {
    int id, fid;
    if (sscanf (key, "exception%d_%d", &id, &fid) == 2) {
       do_add_exception (id, fid);
    }
    return_one_key (c, old_key, "0", 1);

    RETURN(get, 0);
  }

  if (key_len >= 16 && !strncmp (key, "clear_exceptions", 16)) {
    int id;
    if (sscanf (key, "clear_exceptions%d", &id) == 1) {
       int res = do_clear_exceptions (id);
       if (res < 0) {
         RETURN(get, res);
       }
    }
    return_one_key (c, old_key, "0", 1);

    RETURN(get, 0);
  }

  if (key_len >= 11 && !strncmp (key, "suggestions", 11)) {
    int uid, cnt, pos, min_common;
    int t = sscanf (key + 11, "%d#%d%n", &uid, &cnt, &pos);
    if (t != 1 && t != 2) {
      RETURN(get, 0);
    }
    if (t == 1) {
      cnt = MAX_CNT;
    } else {
      int t = sscanf (key + 11 + pos, ",%d", &min_common);
      if (t <= 0) {
        min_common = 1;
      }
    }

    if (2 * cnt + 5 > MAX_FRIENDS) {
      active_aio_queries |= (1 << 19);
      cnt = (MAX_FRIENDS - 5) / 2;
    }

    int res = get_suggestions (uid, cnt, min_common, fr_buff);
    if (res >= 0) {
      char *s = buf;
      int n = fr_buff[0], i;
      s += sprintf (s, "%d", n);
      for (i = 0; i < n; i++) {
        s += sprintf (s, ",%d,%d", fr_buff[i * 2 + 1], fr_buff[i * 2 + 2]);
      }
      return_one_key (c, old_key, buf, s - buf);
    }

    RETURN(get, res);
  }

  RETURN(get, 0);
}