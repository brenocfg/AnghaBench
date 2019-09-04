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
struct cache_local_copy {int dummy; } ;
typedef  int /*<<< orphan*/  dyn_mark_t ;
typedef  int /*<<< orphan*/  cache_top_access_result_t ;
typedef  int /*<<< orphan*/  cache_stat_server_t ;

/* Variables and functions */
 int CACHE_FEATURE_ACCESS_QUERIES ; 
 int CACHE_FEATURE_DETAILED_SERVER_STATS ; 
 int CACHE_FEATURE_LONG_QUERIES ; 
 int /*<<< orphan*/  VALUE_BUFF_SIZE ; 
 int /*<<< orphan*/  access_misses ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  bottom_stats_queries ; 
 int /*<<< orphan*/  cache_acounter (char*,int,double*) ; 
 int /*<<< orphan*/  cache_do_access (char*) ; 
 int cache_do_change_disk_status (int,int,int,int) ; 
 int cache_do_convert (char*,char*,int /*<<< orphan*/ ) ; 
 int cache_do_detailed_server_stats (int /*<<< orphan*/ ***,int) ; 
 int cache_do_local_copies (char*,struct cache_local_copy**) ; 
 int cache_do_memory_stats (char*,int /*<<< orphan*/ ) ; 
 int cache_features_mask ; 
 int cache_get_bottom_disk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  cache_get_file_size (char*,long long*) ; 
 int cache_get_sorted_list (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int cache_get_top_stats (int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int cache_get_yellow_light_remaining (char*,char*,int*,int*) ; 
 int cache_id ; 
 int cache_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  cache_stats_counter_incr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgsl_order_bottom ; 
 int /*<<< orphan*/  cgsl_order_top ; 
 int /*<<< orphan*/  convert_miss_counters ; 
 int /*<<< orphan*/  convert_success_counters ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_access_queries ; 
 int /*<<< orphan*/  get_acounter_queries ; 
 int get_at_prefix_length (char const*,int) ; 
 int /*<<< orphan*/  get_bottom_access_stat ; 
 int /*<<< orphan*/  get_bottom_disk_stat ; 
 int /*<<< orphan*/  get_convert_queries ; 
 int /*<<< orphan*/  get_local_copies_queries ; 
 int /*<<< orphan*/  get_queries ; 
 double get_resource_usage_time () ; 
 int /*<<< orphan*/  get_top_access_stat ; 
 int /*<<< orphan*/  get_top_disk_stat ; 
 int /*<<< orphan*/  get_yellow_time_remaining_queries ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int return_one_key_flags (struct connection*,char const*,char*,int,int) ; 
 int serialize_local_copies_as_text (struct cache_local_copy*,int) ; 
 int serialize_stat_server_as_text (int /*<<< orphan*/ **,int,char*,int /*<<< orphan*/ ) ; 
 int serialize_top_result_as_text (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,...) ; 
 int sscanf (char const*,char*,int*,...) ; 
 char* stats_buff ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  top_stats_queries ; 
 int /*<<< orphan*/  update_query_stat (int /*<<< orphan*/ *,double) ; 
 char* value_buff ; 
 int /*<<< orphan*/  vkprintf (int,char*,double,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  double query_time;
  get_queries++;
  int dog_len = get_at_prefix_length (key, key_len);
  const char *orig_key = key;
  key += dog_len;
  key_len -= dog_len;

  int id, t, limit, r, flags = 0, min_rate = 0, node_id, server_id, disk_id;
  char uri[256], local_uri[256];

  if (key_len < 1) {
    return 0;
  }

  cache_top_access_result_t R;

  switch (*key) {
    case 'a':
      if (!binlog_disabled && (cache_features_mask & CACHE_FEATURE_ACCESS_QUERIES) && key_len >= 6 && !memcmp (key, "access", 6) && sscanf (key + 6, "%d:%255s", &id, uri) == 2) {
        get_access_queries++;
        if (id != cache_id) {
          access_misses++;
        } else {
          cache_do_access (uri);
          return return_one_key (c, orig_key, "1", 1);
        }
      }
      if (key_len >= 8 && !memcmp (key, "acounter", 8) && sscanf (key + 8, "%d:%d:%255s", &id, &t, uri) == 3) {
        get_acounter_queries++;
        if (id == cache_id) {
          double v;
          if (cache_acounter (uri, t, &v) >= 0) {
            return return_one_key (c, orig_key, stats_buff, sprintf (stats_buff, "%.7lg", v));
          }
        }
      }
      break;
    case 'b':
      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 11 && !memcmp (key, "bottom_disk", 11) && sscanf (key + 11, "%d,%d,%d,%d,%d,%d,%d", &id, &t, &limit, &flags, &node_id, &server_id, &disk_id) == 7 && cache_id == id) {
        query_time = -get_resource_usage_time ();
        r = cache_get_bottom_disk (&R, t, cgsl_order_bottom, limit, node_id, server_id, disk_id, flags);
        if (r >= 0) {
          r = serialize_top_result_as_text (&R, value_buff, VALUE_BUFF_SIZE);
        }
        query_time += get_resource_usage_time ();
        update_query_stat (&get_bottom_disk_stat, query_time);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }
      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 13 && !memcmp (key, "bottom_access", 10) && sscanf (key + 13, "%d,%d,%d,%d,%d", &id, &t, &limit, &flags, &min_rate) >= 3 && id == cache_id) {
        query_time = -get_resource_usage_time ();
        r = cache_get_sorted_list (&R, t, cgsl_order_bottom, limit, flags, min_rate);
        if (r >= 0) {
          r = serialize_top_result_as_text (&R, value_buff, VALUE_BUFF_SIZE);
        }
        query_time += get_resource_usage_time ();
        update_query_stat (&get_bottom_access_stat, query_time);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }

      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 12 && !memcmp (key, "bottom_stats", 12) && sscanf (key + 12, "%d,%d,%d", &id, &t, &limit) == 3 && id == cache_id) {
        bottom_stats_queries++;
        r = cache_get_top_stats (t, cgsl_order_bottom, limit, value_buff, VALUE_BUFF_SIZE);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }
      break;
    case 'c':
      if (key_len >= 7 && key_len < 1024 && !memcmp (key, "convert", 7) && sscanf (key + 7, "%d:%255s", &id, uri) == 2) {
        get_convert_queries++;
        if (id == cache_id) {
          int r = cache_do_convert (uri, value_buff, VALUE_BUFF_SIZE);
          if (r == 1) {
            cache_stats_counter_incr (convert_success_counters);
            return return_one_key (c, orig_key, value_buff, strlen (value_buff));
          }
          cache_stats_counter_incr (convert_miss_counters);
          if (r == 0) {
            return return_one_key_flags (c, orig_key, "b:0;", 4, 1);
          }
        }
      }
      break;
    case 'd':
      if (!binlog_disabled && key_len >= 14 && !memcmp (key, "disable_server", 14) && sscanf (key + 14, "%d,%d,%d", &id, &node_id, &server_id) == 3 && cache_id == id) {
        int r = cache_do_change_disk_status (node_id, server_id, 0, 0);
        if (r > 0) {
          return_one_key_flags (c, orig_key, "b:1;", 4, 1);
        } else {
          return_one_key_flags (c, orig_key, "b:0;", 4, 1);
        }
        return 0;
      }

      if (!binlog_disabled && key_len >= 12 && !memcmp (key, "disable_disk", 12) && sscanf (key + 12, "%d,%d,%d,%d", &id, &node_id, &server_id, &disk_id)== 4 && cache_id == id) {
        int r = cache_do_change_disk_status (node_id, server_id, disk_id, 0);
        if (r > 0) {
          return_one_key_flags (c, orig_key, "b:1;", 4, 1);
        } else {
          return_one_key_flags (c, orig_key, "b:0;", 4, 1);
        }
        return 0;
      }

      if ((cache_features_mask & CACHE_FEATURE_DETAILED_SERVER_STATS) && key_len >= 21 && !memcmp (key, "detailed_server_stats", 21) && sscanf (key + 21, "%d,%d", &id, &flags) >= 1 && cache_id == id) {
        dyn_mark_t mrk;
        cache_stat_server_t **A;
        dyn_mark (mrk);
        int r = cache_do_detailed_server_stats (&A, flags);
        if (r > 0) {
          r = serialize_stat_server_as_text (A, r, value_buff, VALUE_BUFF_SIZE);
        }
        dyn_release (mrk);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
        return 0;
      }
      break;
    case 'e':
      if (!binlog_disabled && key_len >= 13 && !memcmp (key, "enable_server", 13) && sscanf (key + 13, "%d,%d,%d", &id, &node_id, &server_id) == 3 && cache_id == id) {
        int r = cache_do_change_disk_status (node_id, server_id, 0, 1);
        if (r > 0) {
          return_one_key_flags (c, orig_key, "b:1;", 4, 1);
        } else {
          return_one_key_flags (c, orig_key, "b:0;", 4, 1);
        }
        return 0;
      }

      if (!binlog_disabled && key_len >= 11 && !memcmp (key, "enable_disk", 11) && sscanf (key + 11, "%d,%d,%d,%d", &id, &node_id, &server_id, &disk_id)== 4 && cache_id == id) {
        int r = cache_do_change_disk_status (node_id, server_id, disk_id, 1);
        if (r > 0) {
          return_one_key_flags (c, orig_key, "b:1;", 4, 1);
        } else {
          return_one_key_flags (c, orig_key, "b:0;", 4, 1);
        }
        return 0;
      }
      break;
    case 'f':
      if (key_len >= 9 && !memcmp (key, "file_size", 9) && sscanf (key + 9, "%d:%255s", &id, uri) == 2 && id == cache_id) {
        long long s;
        if (cache_get_file_size (uri, &s) < 0) {
          return 0;
        }
        return return_one_key (c, orig_key, value_buff, sprintf (value_buff, "%lld", s));
      }
      break;
    case 'l':
      if (key_len >= 12 && key_len < 1024 && !memcmp (key, "local_copies", 12) && sscanf (key + 12, "%d:%255s", &id, uri) == 2) {
        get_local_copies_queries++;
        if (id == cache_id) {
          struct cache_local_copy *LC;
          int r = cache_do_local_copies (uri, &LC);
          if (r >= 0) {
            r = serialize_local_copies_as_text (LC, r);
            if (r >= 0) {
              return return_one_key (c, orig_key, value_buff, r);
            }
          }
        }
      }
      break;
    case 'm':
      if (key_len >= 12 && !memcmp (key, "memory_stats", 12)) {
        int r = cache_do_memory_stats (value_buff, VALUE_BUFF_SIZE);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }
      break;
    case 's':
      if (key_len >= 5 && !strncmp (key, "stats", 5)) {
        int len = cache_prepare_stats (c);
        return return_one_key (c, orig_key, stats_buff, len);
      }
      break;
    case 't':
      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 10 && !memcmp (key, "top_access", 10) && sscanf (key + 10, "%d,%d,%d,%d,%d", &id, &t, &limit, &flags, &min_rate) >= 3 && id == cache_id) {
        query_time = -get_resource_usage_time ();
        r = cache_get_sorted_list (&R, t, cgsl_order_top, limit, flags, min_rate);
        if (r >= 0) {
          r = serialize_top_result_as_text (&R, value_buff, VALUE_BUFF_SIZE);
        }
        query_time += get_resource_usage_time ();
        update_query_stat (&get_top_access_stat, query_time);
        vkprintf (1, "top_access execution time: %.6lfs, returned value: %d.\n", query_time, r);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }

      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 8 && !memcmp (key, "top_disk", 8) && sscanf (key + 8, "%d,%d,%d,%d,%d,%d,%d", &id, &t, &limit, &flags, &node_id, &server_id, &disk_id) == 7 && cache_id == id) {
        query_time = -get_resource_usage_time ();
        r = cache_get_bottom_disk (&R, t, cgsl_order_top, limit, node_id, server_id, disk_id, flags);
        if (r >= 0) {
          r = serialize_top_result_as_text (&R, value_buff, VALUE_BUFF_SIZE);
        }
        query_time += get_resource_usage_time ();
        update_query_stat (&get_top_disk_stat, query_time);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }

      if ((cache_features_mask & CACHE_FEATURE_LONG_QUERIES) && key_len >= 9 && !memcmp (key, "top_stats", 9) && sscanf (key + 9, "%d,%d,%d", &id, &t, &limit) == 3 && id == cache_id) {
        top_stats_queries++;
        r = cache_get_top_stats (t, cgsl_order_top, limit, value_buff, VALUE_BUFF_SIZE);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, r);
        }
      }
      break;
    case 'y':
      if (key_len >= 21 && !memcmp (key, "yellow_time_remaining", 21) && sscanf (key + 21, "%d:%255[^~]~%255s", &id, uri, local_uri) == 3 && id == cache_id) {
        int remaining_time, elapsed_time;
        get_yellow_time_remaining_queries++;
        r = cache_get_yellow_light_remaining (uri, local_uri, &remaining_time, &elapsed_time);
        if (r >= 0) {
          return return_one_key (c, orig_key, value_buff, sprintf (value_buff, "%d,%d", remaining_time, elapsed_time));
        } else {
          return return_one_key (c, orig_key, "NOT_FOUND", 9);
        }
      }
      break;
  }

  return 0;
}