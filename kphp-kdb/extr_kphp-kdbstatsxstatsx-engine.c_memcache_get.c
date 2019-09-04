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
typedef  void counter ;
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeCnt ; 
 int MAX_RECORD_WORDS ; 
 int /*<<< orphan*/ * NewAllocations ; 
 int Q_raw ; 
 int /*<<< orphan*/  SplitBlocks ; 
 int /*<<< orphan*/  UsedCnt ; 
 int /*<<< orphan*/  assert (int) ; 
 int counter_serialize (void*,char*) ; 
 int /*<<< orphan*/  debug_error (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  debug_key (char const*,int) ; 
 int disable_counter (long long,int /*<<< orphan*/ ) ; 
 int enable_counter (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_at_prefix_length (char const*,int) ; 
 int get_counter_serialized (char*,long long,int) ; 
 int get_counter_versions (char*,long long) ; 
 int get_counter_views (long long) ; 
 int get_counter_views_given_version (long long,int) ; 
 int get_counter_visitors (long long) ; 
 int get_counter_visitors_given_version (long long,int) ; 
 void* get_counters_sum (int,int,int) ; 
 int get_monthly_views_serialized (char*,long long) ; 
 int get_monthly_visitors_serialized (char*,long long) ; 
 int get_timezone (long long) ; 
 int memcache_wait (struct connection*) ; 
 int not_found (struct connection*) ; 
 int /*<<< orphan*/  parse_countid_with_version (char const*,long long*,int*) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  return_one_key_list (struct connection*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int set_timezone (long long,int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 int sscanf (char const*,char*,...) ; 
 char* stats_buff ; 
 int stats_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 long long strtoll (char const*,char**,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_get (struct connection *c, const char *key, int len) {
  char *ptr;
  //char timezone[32];
  long long cnt_id;
  if (verbosity >= 4) {
    fprintf (stderr, "memcache_get (key = \"");
    debug_key (key, len);
    fprintf (stderr, "\")\n");
  }
  int dog_len = get_at_prefix_length (key, len);
  key += dog_len;
  len -= dog_len;

  Q_raw = 0;
  if (len > 0 && *key == '%') {
    dog_len ++;
    key ++;
    len --;
    Q_raw = 1;
  }


  if (len > 5 && !strncmp (key, "views", 5)) {
    int ver;
    if (!parse_countid_with_version (key + 5, &cnt_id, &ver)) {
      debug_error ("get", "couldn't parse count_id&version", key, len);
      return not_found (c);
    }
    //int res = get_counter_views(cnt_d, ver); TODO!!!
    int res = (ver == -1) ? get_counter_views (cnt_id) : get_counter_views_given_version (cnt_id,ver);
    if (res == -2) {
      return memcache_wait (c);
    }
    if (res >= 0) {
      //int return_one_key (struct connection *c, const char *key, char *val, int vlen) {
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
    }
    return 0;
  }

  if (len > 8 && !strncmp (key, "visitors", 8)) {
    int ver;
    if (!parse_countid_with_version (key + 8, &cnt_id, &ver)) {
      debug_error ("get","couldn't parse count_id&version",key, len);
      return not_found(c);
    }
    //int res = get_counter_visitors(cnt_id, ver); TODO !!!
    int res = (ver == -1) ? get_counter_visitors (cnt_id) : get_counter_visitors_given_version (cnt_id, ver);
    if (res == -2) {
      return memcache_wait (c);
    }
    if (res >= 0) {
      //int return_one_key (struct connection *c, const char *key, char *val, int vlen) {
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
    }
    return 0;
  }

  if (len > 14 && !strncmp (key, "enable_counter", 14)) {
    cnt_id = strtoll (key + 14, &ptr, 10);
    if (ptr > key + 14 && !*ptr) {
      int res = enable_counter (cnt_id, 0);
      if (res >= 0) {
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
      }
      return 0;
    }
  }

  if (len > 15 && !strncmp (key, "disable_counter", 15)) {
    cnt_id = strtoll (key + 15, &ptr, 10);
    if (ptr > key + 15 && !*ptr) {
      int res = disable_counter (cnt_id, 0);
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
      return 0;
    }
  }

  if (len > 12 && !strncmp(key, "set_timezone", 12)) {
    int tz = 0;
    //if (2 == sscanf(key+12,"%d#%31s",&cnt_id,timezone)) {
    if (2 == sscanf(key + 12,"%lld#%d", &cnt_id, &tz)) {
      tz = tz + 12 + 4;
      if (tz < 0) {
        return 0;
      }
      int res = set_timezone (cnt_id, tz, 0);
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
      return 0;
    }
  }

  if (len > 8 && !strncmp(key, "timezone", 8)) {
    if (1 == sscanf(key + 8, "%lld", &cnt_id)) {
      int res = get_timezone (cnt_id);
      if (!Q_raw) {
        return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
      } else {
        *(int *)stats_buff = res;
        return_one_key (c, key - dog_len, stats_buff, sizeof (int));
      }
      return 0;
    }
  }


  if (len > 7 && !strncmp (key, "counter", 7)) {
    int ver = 0;
    if (sscanf (key, "counter%lld@%d", &cnt_id, &ver) >= 1) {
      int to_serialize = key[strlen(key) - 1] != '?';
      if (verbosity >= 4) {
        fprintf(stderr, "cnt_id = %lld, ver = %d\n", cnt_id, ver);
      }
      int res = get_counter_serialized (stats_buff, cnt_id, ver);
      if (res == -2) {
        return memcache_wait (c);
      }
      if (res > 0) {
        if (to_serialize && !Q_raw) {
          write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 1 %d\r\n", key - dog_len, res));
        } else {
          write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 0 %d\r\n", key - dog_len, res));
        }
        write_out (&c->Out, stats_buff, res);
        write_out (&c->Out, "\r\n", 2);
      }
      return 0;
    }
  }

  if (len > 16 && !strncmp (key, "monthly_visitors", 16)) {
    cnt_id = 0;
    if (sscanf (key, "monthly_visitors%lld", &cnt_id) >= 1) {
      int res = get_monthly_visitors_serialized (stats_buff, cnt_id);
      if (res == -2) {
        return memcache_wait (c);
      }
      if (res >= 0) {
        return_one_key (c, key - dog_len, stats_buff, res);
      }
      return 0;
    }
  }

  if (len > 13 && !strncmp (key, "monthly_views", 13)) {
    cnt_id = 0;
    if (sscanf (key, "monthly_views%lld", &cnt_id) >= 1) {
      int res = get_monthly_views_serialized (stats_buff, cnt_id);
      if (res == -2) {
        return memcache_wait (c);
      }
      if (res >= 0) {
        return_one_key (c, key - dog_len, stats_buff, res);
      }
      return 0;
    }
  }

  if (len > 12 && !strncmp (key, "counters_sum", 12)) {
    int start_id = 0, finish_id = 0, id = 0;
    int to_serialize = key[strlen(key) - 1] != '?';
    if (sscanf (key, "counters_sum%d_%d_%d", &id, &start_id, &finish_id)) {
      struct counter *C = get_counters_sum (id, start_id, finish_id);
      if (C == (void *)-2l) { 
        return memcache_wait (c);
      }
      if (C) {
        int res = counter_serialize (C, stats_buff);
        assert (res >= 0);
        if (to_serialize && !Q_raw) {
          write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 1 %d\r\n", key - dog_len, res));
        } else {
          write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 0 %d\r\n", key - dog_len, res));
        }
        write_out (&c->Out, stats_buff, res);
        write_out (&c->Out, "\r\n", 2);
      }
    }
  }
  /*
  if (len > 7 && !strncmp (key, "counter", 7)) {
    int cnt_id, subcnt_id = -1, ver = 0;
    if (sscanf (key, "counter%d:%d@%d", &cnt_id, &subcnt_id, &ver) >= 2) {
      //int res = get_counter_serialized (stats_buff, cnt_id, subcnt_id, ver); TODO !!!
      int res = get_counter_serialized (stats_buff, cnt_id, ver);
      if (res > 0) {
        write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 1 %d\r\n", key, res));
        write_out (&c->Out, stats_buff, res);
        write_out (&c->Out, "\r\n", 2);
      }
      return 0;
    }
    if (sscanf (key, "counter%d@%d", &cnt_id, &ver) == 2) {
      //int res = get_counter_serialized (stats_buff, cnt_id, -1, ver); TODO !!!
      int res = get_counter_serialized (stats_buff, cnt_id, ver);
      if (res > 0) {
        write_out (&c->Out, stats_buff+res, sprintf (stats_buff+res, "VALUE %s 1 %d\r\n", key, res));
        write_out (&c->Out, stats_buff, res);
        write_out (&c->Out, "\r\n", 2);
      }
      return 0;
    }
  }
  */

  if (len > 8 && !strncmp (key, "versions", 8)) {
    cnt_id = strtoll (key + 8, &ptr, 10);
    if (ptr > key+8 && !*ptr) {
      int res = get_counter_versions (stats_buff, cnt_id);
      if (res == -2) {
        return memcache_wait (c);
      }
      if (res > 0) {
        write_out (&c->Out, stats_buff + res, sprintf (stats_buff + res, "VALUE %s 0 %d\r\n", key - dog_len, res));
        write_out (&c->Out, stats_buff, res);
        write_out (&c->Out, "\r\n", 2);
      }
      return 0;
    }
  }

  if (len >= 16 && !strncmp (key, "free_block_stats", 16)) {
    return_one_key_list (c, key - dog_len, len + dog_len, MAX_RECORD_WORDS, 0, FreeCnt, MAX_RECORD_WORDS);
    return 0;
  }

  if (len >= 16 && !strncmp (key, "used_block_stats", 16)) {
    return_one_key_list (c, key - dog_len, len + dog_len, MAX_RECORD_WORDS, 0, UsedCnt, MAX_RECORD_WORDS);
    return 0;
  }

  if (len >= 16 && !strncmp (key, "allocation_stats", 16)) {
    return_one_key_list (c, key - dog_len, len + dog_len, MAX_RECORD_WORDS, 0, NewAllocations[0], MAX_RECORD_WORDS * 4);
    return 0;
  }

  if (len >= 17 && !strncmp (key, "split_block_stats", 17)) {
    return_one_key_list (c, key - dog_len, len + dog_len, MAX_RECORD_WORDS, 0, SplitBlocks, MAX_RECORD_WORDS);
    return 0;
  }

  if (len >= 5 && !strncmp (key, "stats", 5)) {
    return_one_key (c, key - dog_len, stats_buff, stats_prepare_stats (c));
    return 0;
  }

  return 0;
}