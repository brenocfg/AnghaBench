#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ disabled; } ;
typedef  TYPE_1__ volume_t ;
struct connection {int /*<<< orphan*/  Out; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int STORAGE_ERR_SCANDIR_MULTIPLE ; 
 int STORAGE_ERR_SIZE_MISMATCH ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_disabled ; 
 int /*<<< orphan*/  create_write_thread (struct connection*,int /*<<< orphan*/ ,TYPE_1__*,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_unknown ; 
 scalar_t__ force_write_index ; 
 int gen_volumes_list () ; 
 int get_at_prefix_length (char const*,int) ; 
 int get_dir_id_by_name (char const*) ; 
 int /*<<< orphan*/  get_dirs_serialized (char*) ; 
 int /*<<< orphan*/  get_file_queries ; 
 int /*<<< orphan*/  get_hide_queries ; 
 int /*<<< orphan*/  get_misses ; 
 int /*<<< orphan*/  get_queries ; 
 TYPE_1__* get_volume_f (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_volume_misses ; 
 int get_volume_serialized (char*,long long) ; 
 int get_volume_text (char*,long long) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 int sprintf (char*,char*,...) ; 
 int sscanf (char const*,char*,long long*,...) ; 
 char* stats_buff ; 
 int storage_close_binlog_file (TYPE_1__*,int) ; 
 int storage_enable_binlog_file (TYPE_1__*,int) ; 
 int storage_prepare_stats (struct connection*) ; 
 int storage_scan_dir (int) ; 
 int storage_volume_check_file (TYPE_1__*,double,long long) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* value_buff ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  vkprintf (3, "memcache_get (c = %p, %.*s)\n", c, key_len, key);
  get_queries++;
  int dog_len = get_at_prefix_length (key, key_len);
  key += dog_len;
  key_len -= dog_len;

  long long volume_id;
  char path[1024];
  int has_path = 0;
  int hide_local_id;

  if (key_len >= 4 && !memcmp (key, "file", 4) && sscanf (key+4, "%lld,%1023s", &volume_id, path) == 2) {
    get_file_queries++;
    has_path = 1;
  }

  if (key_len >= 4 && !memcmp (key, "hide", 4) && sscanf (key+4, "%lld,%x", &volume_id, &hide_local_id) == 2) {
    vkprintf (4, "HIDE\n");
    get_hide_queries++;
    assert (snprintf (path, sizeof (path), "**hide doc**%x", hide_local_id) < sizeof (path));
    has_path = 1;
  }

  if (has_path) {
    vkprintf (4, "path: %s\n", path);
    volume_t *V = get_volume_f (volume_id, 0);
    if (V == NULL) {
      get_volume_misses++;
      get_misses++;
      return 0;
    }

    if (V->disabled || binlog_disabled || force_write_index) {
      return 0;
    }
    create_write_thread (c, 0, V, key + dog_len, path, NULL, 0, ct_unknown);
    return 0;
  }

  int l;
  double percent = 0.0;
  long long file_size;
  if (key_len >= 10 && !memcmp (key, "check_file", 10) && (l = sscanf (key + 10, "%lld,%lld,%lf", &volume_id, &file_size, &percent)) >= 2) {
    if (l == 2) {
      percent = 99.0;
    }
    if (percent < 0.0) {
      percent = 0.0;
    }
    if (percent > 100.0) {
      percent = 100.0;
    }
    volume_t *V = get_volume_f (volume_id, 0);
    if (V == NULL) {
      get_volume_misses++;
      get_misses++;
      return 0;
    }
    if (V->disabled || binlog_disabled || force_write_index) {
      return 0;
    }
    l = storage_volume_check_file (V, percent * 0.01, file_size);
    return return_one_key (c, key - dog_len, value_buff, sprintf (value_buff, "%d", l));
  }

  if (key_len == 7 && !memcmp (key, "volumes", 7) && (l = gen_volumes_list ()) >= 0) {
    return return_one_key (c, key - dog_len, value_buff, l);
  }

  if (key_len >= 6 && !memcmp (key, "volume", 6) && sscanf (key + 6, "%lld", &volume_id) == 1 &&
      (l = get_volume_serialized (value_buff, volume_id) ) >= 0) {
    write_out (&c->Out, value_buff+l, sprintf (value_buff+l, "VALUE %s 1 %d\r\n", key - dog_len, l));
    write_out (&c->Out, value_buff, l);
    write_out (&c->Out, "\r\n", 2);
    return 0;
  }

  if (key_len >= 6 && !memcmp (key, "Volume", 6) && sscanf (key + 6, "%lld", &volume_id) == 1 &&
      (l = get_volume_text (value_buff, volume_id)) >= 0) {
    return return_one_key (c, key - dog_len, value_buff, l);
  }

  if (key_len == 4 && !memcmp (key, "dirs", 4) && !get_dirs_serialized (value_buff)) {
    l = strlen (value_buff);
    write_out (&c->Out, value_buff+l, sprintf (value_buff+l, "VALUE %s 1 %d\r\n", key - dog_len, l));
    write_out (&c->Out, value_buff, l);
    write_out (&c->Out, "\r\n", 2);
    return 0;
  }

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = storage_prepare_stats (c);
    return return_one_key (c, key - dog_len, stats_buff, len);
  }

  int dir_id = -1;

  if (key_len >= 11 && !memcmp (key, "enable_file", 11) && sscanf (key + 11, "%lld,%d", &volume_id, &dir_id) == 2) {
    volume_t *V = get_volume_f (volume_id, 0);
    if (V == NULL) {
      get_misses++;
      return 0;
    }
    l = storage_enable_binlog_file (V, dir_id);
    if (l == STORAGE_ERR_SIZE_MISMATCH) {
      return return_one_key (c, key - dog_len, "2", 1);
    }
    if (l < 0) {
      vkprintf (0, "enable_file%lld,%d returns error code %d.\n", volume_id, dir_id, l);
    }
    return return_one_key (c, key - dog_len, l < 0 ? "0" : "1", 1);
  }

  if (key_len >= 12 && !memcmp (key, "disable_file", 12) && sscanf (key + 12, "%lld,%d", &volume_id, &dir_id) == 2) {
    volume_t *V = get_volume_f (volume_id, 0);
    if (V == NULL) {
      get_misses++;
      return 0;
    }
    l = storage_close_binlog_file (V, dir_id);
    return return_one_key (c, key - dog_len, l < 0 ? "0" : "1", 1);
  }

  if (key_len >= 7 && !memcmp (key, "scandir", 7)) {
    char *msg;
    int dir_id = get_dir_id_by_name (key + 7);
    if (dir_id < 0) {
      msg = "Path wasn't found";
      return return_one_key (c, key - dog_len, msg, strlen (msg));
    }
    int r = storage_scan_dir (dir_id);
    if (r == STORAGE_ERR_SCANDIR_MULTIPLE) {
      msg = "Couldn't scandir more than once";
      return return_one_key (c, key - dog_len, msg, strlen (msg));
    } else {
      return return_one_key (c, key - dog_len, value_buff, sprintf (value_buff, "%d", r));
    }
  }

/*
  if (key_len >= 11 && !memcmp (key, "disable_dir", 11) && sscanf (key + 11, "%d", &dir_id) == 1) {
    l = change_dir_write_status (dir_id, 1);
    if (l < 0) {
      return 0;
    }
    get_hits++;
    return return_one_key (c, key - dog_len, value_buff, sprintf (value_buff, "%d", l));
  }

  if (key_len >= 10 && !memcmp (key, "enable_dir", 10) && sscanf (key + 10, "%d", &dir_id) == 1) {
    l = change_dir_write_status (dir_id, 0);
    if (l < 0) {
      return 0;
    }
    get_hits++;
    return return_one_key (c, key - dog_len, value_buff, sprintf (value_buff, "%d", l));
  }
*/
  get_misses++;
  return 0;
}