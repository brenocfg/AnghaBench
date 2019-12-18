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
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_disabled ; 
 int /*<<< orphan*/  cache_do_delete_local_copy (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_do_set_new_local_copy (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_do_set_size (char*,long long) ; 
 int /*<<< orphan*/  cache_do_set_yellow_light_remaining (char*,char*,int) ; 
 int cache_id ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int read_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_delete_local_copy_queries ; 
 int /*<<< orphan*/  set_file_size_queries ; 
 int /*<<< orphan*/  set_new_local_copy_queries ; 
 int /*<<< orphan*/  set_queries ; 
 int /*<<< orphan*/  set_yellow_time_remaining_queries ; 
 int sscanf (char const*,char*,...) ; 
 int /*<<< orphan*/ * value_buff ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  int id;
  char uri[256], local_uri[256];

  if (op != 1 || key_len < 1 || binlog_disabled) {
    return -2;
  }
  set_queries++;

  switch (*key) {
    case 'd':
      if (key_len >= 17 && size < 256 && !memcmp (key, "delete_local_copy", 17) && sscanf (key + 17, "%d:%255s", &id, uri) == 2 && id == cache_id) {
        assert (read_in (&c->In, value_buff, size) == size);
        value_buff[size] = 0;
        set_delete_local_copy_queries++;
        return (cache_do_delete_local_copy (uri, value_buff) < 0) ? 0 : 1;
      }
      break;
    case 'f':
      if (key_len >= 9 && size <= 64 && !memcmp (key, "file_size", 9) && sscanf (key + 9, "%d:%255s", &id, uri) == 2 && id == cache_id) {
        long long s;
        assert (read_in (&c->In, value_buff, size) == size);
        value_buff[size] = 0;
        if (sscanf (value_buff, "%lld", &s) == 1) {
          set_file_size_queries++;
          if (!cache_do_set_size (uri, s)) {
            return 1;
          }
        }
        return 0;
      }
      break;
    case 'n':
      if (key_len >= 14 && size < 256 && !memcmp (key, "new_local_copy", 14) && sscanf (key + 14, "%d:%255s", &id, uri) == 2 && id == cache_id) {
        assert (read_in (&c->In, value_buff, size) == size);
        value_buff[size] = 0;
        set_new_local_copy_queries++;
        return (cache_do_set_new_local_copy (uri, value_buff) < 0) ? 0 : 1;
      }
      break;
    case 'y':
      if (key_len >= 21 && size < 256 && !memcmp (key, "yellow_time_remaining", 21) && sscanf (key + 21, "%d:%255[^~]~%255s", &id, uri, local_uri) == 3 && id == cache_id) {
        assert (read_in (&c->In, value_buff, size) == size);
        value_buff[size] = 0;
        int duration;
        if (sscanf (value_buff, "%d", &duration) == 1) {
          set_yellow_time_remaining_queries++;
          if (!cache_do_set_yellow_light_remaining (uri, local_uri, duration)) {
            return 1;
          }
        }
        return 0;
      }
      break;
  }
  return -2;
}