#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_5__ {char* text; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LOG ; 
 int /*<<< orphan*/  INIT ; 
 int MAX_ALBUMS ; 
 int MAX_PHOTOS ; 
 int MAX_PHOTOS_DYN ; 
 TYPE_1__* MESSAGE (struct connection*) ; 
 char* NOK ; 
 char* OK ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOG_VERBOSITY ; 
 scalar_t__ STATS_BUFF_SIZE ; 
 scalar_t__ base64url_to_secret (char*,unsigned long long*) ; 
 scalar_t__ binlog_disabled ; 
 double cmd_time ; 
 int compute_uncommitted_log_bytes () ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  delete ; 
 char* dl_pstr (char*,int) ; 
 int do_add_photo_location (int,int,int,int,int,int,int,char*,int) ; 
 int do_add_photo_location_engine (int,int,int,char,int,int,int,int,unsigned long long) ; 
 int do_change_album_order (int,int,int,int) ; 
 int do_change_photo_location_server (int,int,int,int,int) ; 
 int do_change_photo_order (int,int,int,int) ; 
 int do_create_album (int) ; 
 int do_create_album_force (int,int) ; 
 int do_create_photo (int,int,int) ; 
 int do_create_photo_force (int,int,int,int) ; 
 int do_del_photo_location (int,int,int) ; 
 int do_del_photo_location_engine (int,int,int,char,int) ; 
 int do_increment_album_field (int,int,char*,int) ; 
 int do_increment_photo_field (int,int,char*,int) ; 
 int do_restore_photo (int,int) ; 
 int do_restore_photo_location (int,int) ; 
 int do_rotate_photo (int,int,int) ; 
 int do_save_photo_location (int,int) ; 
 int do_set_volume (int,int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  flush_binlog () ; 
 int /*<<< orphan*/  get ; 
 int get_album (int,int,int /*<<< orphan*/ ,char*,char**) ; 
 int get_albums (int,int,int,char*,int,int,char*,char**) ; 
 int get_albums_count (int,char*) ; 
 int get_photo (int,int,int,char*,char**) ; 
 int get_photos (int,int,int,int,char*,int,int,char*,char**) ; 
 int get_photos_count (int,int,char*) ; 
 int get_photos_overview (int,char*,int,int,char*,int,int,char**) ; 
 int /*<<< orphan*/  hst (char*,char const*,int) ; 
 long long log_pos ; 
 size_t mode ; 
 char** mode_names ; 
 int /*<<< orphan*/  msg_free (TYPE_1__*) ; 
 scalar_t__ msg_verify (TYPE_1__*,int) ; 
 double mytime () ; 
 int photo_prepare_stats () ; 
 int prepare_stats (struct connection*,char*,scalar_t__) ; 
 int /*<<< orphan*/  read_new_events () ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  return_one_key_flags (struct connection*,char const*,char*,int,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,...) ; 
 char* stats_buff ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  sync ; 
 scalar_t__ write_only ; 

int memcache_try_get (struct connection *c, const char *old_key, int old_key_len) {
  hst ("memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);

  char *key;
  int key_len;
  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = photo_prepare_stats();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }

  if (key_len >= 11 && !strncmp (key, "synchronize", 11)) {
    INIT;

    if (write_only && !key[11]) {
      flush_binlog();

      char *ret = dl_pstr ("%lld", log_pos + compute_uncommitted_log_bytes());
      return_one_key (c, old_key, ret, strlen (ret));
    }

    long long binlog_pos = -1;
    int cur;
    if (binlog_disabled && sscanf (key + 11, "%lld%n", &binlog_pos, &cur) == 1 && !key[cur + 11]) {
      int iter = 0;
      while (log_pos < binlog_pos) {
        if (++iter % 1000 == 0 && mytime() + cmd_time > 0.5) {
          break;
        }
        read_new_events();
      }
      if (log_pos < binlog_pos) {
        return_one_key (c, old_key, NOK, strlen (NOK));
      } else {
        return_one_key (c, old_key, OK, strlen (OK));
      }
    }

    RETURN (sync, 0);
  }

  GET_LOG;

  SET_LOG_VERBOSITY;

  INIT;

  if (key_len >= 10 && !strncmp (key, "set_volume", 10)) {
    int volume_id, server_id, cur;
    if (sscanf (key + 10, "%d,%d%n", &volume_id, &server_id, &cur) < 2 || key[cur + 10]) {
      RETURN (set, 0);
    }

    int res = do_set_volume (volume_id, server_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));
    }

    RETURN (set, 0);
  }

  if (key_len >= 25 && !strncmp (key, "add_", 4) && !strncmp (key + 4, mode_names[mode], 5) && (!strncmp (key + 9, "_location_engine", 16) || !strncmp (key + 9, "_original_location_engine", 25))) {
    int user_id, photo_id, original = (key[10] == 'o'), volume_id, local_id, extra, cur, add = 25 + 9 * original;
    char size;
    unsigned long long secret;
    char base64url_secret[12];
    int rotate = 0;
    if ('0' <= key[add] && key[add] <= '3') {
      rotate = key[add++] - '0';
    }
    if (sscanf (key + add, "_%c%d,%d,%d,%x,%d,%11[0-9A-Za-z_-]%n", &size, &user_id, &photo_id, &volume_id, &local_id, &extra, base64url_secret, &cur) < 7 ||
                key[cur + add] || base64url_to_secret (base64url_secret, &secret)) {
      RETURN (set, 0);
    }

    int res = do_add_photo_location_engine (user_id, photo_id, original, size, rotate, volume_id, local_id, extra, secret);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 25 && !strncmp (key, "del_", 4) && !strncmp (key + 4, mode_names[mode], 5) && (!strncmp (key + 9, "_location_engine", 16) || !strncmp (key + 9, "_original_location_engine", 25))) {
    int user_id, photo_id, original = (key[10] == 'o'), rotate = -1, cur, add = 25 + 9 * original;
    char size = -1;
    if ('0' <= key[add] && key[add] <= '3') {
      rotate = key[add++] - '0';
    }
    if (key[add++] != '_') {
      RETURN (delete, 0);
    }
    if ('a' <= key[add] && key[add] <= 'z') {
      size = key[add++];
    }
    if (sscanf (key + add, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + add]) {
      RETURN (delete, 0);
    }

    int res = do_del_photo_location_engine (user_id, photo_id, original, size, rotate);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (delete, 0);
    }

    RETURN (delete, res);
  }

  if (key_len >= 18 && !strncmp (key, "add_", 4) && !strncmp (key + 4, mode_names[mode], 5) && (!strncmp (key + 9, "_location", 9) || !strncmp (key + 9, "_original_location", 18))) {
    int user_id, photo_id, original = (key[10] == 'o'), server_id, server_id2, orig_owner_id, orig_album_id, cur, add = 18 + 9 * original;
    if (sscanf (key + add, "%d,%d,%d,%d,%d,%d%n", &user_id, &photo_id, &server_id, &server_id2, &orig_owner_id, &orig_album_id, &cur) < 6 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (set, 0);
    }
    dbg ("do_add_photo_location (user_id = %d)\n", user_id);
    int res = do_add_photo_location (user_id, photo_id, original, server_id, server_id2, orig_owner_id, orig_album_id, key + add + cur + 1, key_len - 1 - cur - add - 1);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 28 && !strncmp (key, "change_", 7) && !strncmp (key + 7, mode_names[mode], 5) && (!strncmp (key + 12, "_location_server", 16) || !strncmp (key + 12, "_original_location_server", 25))) {
    int user_id, photo_id, original = (key[13] == 'o'), server_num = 0, server_id = -1, cur, add = 28 + 9 * original;
    if (sscanf (key + add, "%d,%d,%d%n,%d%n", &user_id, &photo_id, &server_id, &cur, &server_num, &cur) < 3 || key[cur + add]) {
      RETURN (set, 0);
    }
    if (server_num >= 1) {
      server_num--;
    }

    int res = do_change_photo_location_server (user_id, photo_id, original, server_num, server_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 18 && !strncmp (key, "del_", 4) && !strncmp (key + 4, mode_names[mode], 5) && (!strncmp (key + 9, "_location", 9) || !strncmp (key + 9, "_original_location", 18))) {
    int user_id, photo_id, original = (key[10] == 'o'), cur, add = 18 + 9 * original;
    if (sscanf (key + add, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + add]) {
      RETURN (delete, 0);
    }

    int res = do_del_photo_location (user_id, photo_id, original);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (delete, 0);
    }

    RETURN (delete, res);
  }

  if (key_len >= 19 && !strncmp (key, "save_", 5) && !strncmp (key + 5, mode_names[mode], 5) && !strncmp (key + 10, "_location", 9)) {
    int user_id, photo_id, cur;
    if (sscanf (key + 19, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + 19]) {
      RETURN (set, 0);
    }

    int res = do_save_photo_location (user_id, photo_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 22 && !strncmp (key, "restore_", 8) && !strncmp (key + 8, mode_names[mode], 5) && !strncmp (key + 13, "_location", 9)) {
    int user_id, photo_id, cur;
    if (sscanf (key + 22, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + 22]) {
      RETURN (set, 0);
    }

    int res = do_restore_photo_location (user_id, photo_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 12 && !strncmp (key, "rotate_", 7) && !strncmp (key + 7, mode_names[mode], 5)) {
    int dir, user_id, photo_id, cur;
    if (sscanf (key + 12, "%d,%d,%d%n", &user_id, &photo_id, &dir, &cur) < 3 || key[cur + 12]) {
      RETURN (set, 0);
    }

    int res = do_rotate_photo (user_id, photo_id, dir);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 18 && !strncmp (key, "change_", 7) && !strncmp (key + 7, mode_names[mode], 5) && !strncmp (key + 12, "_order", 6)) {
    int add = 18, is_next = 0;
    if (!strncmp (key + add, "_next", 5)) {
      is_next = 1;
      add += 5;
    }

    int user_id, photo_id, photo_id_near, cur;
    if (sscanf (key + add, "%d,%d,%d%n", &user_id, &photo_id, &photo_id_near, &cur) != 3 || key[cur + add]) {
      RETURN (set, 0);
    }

    int res = do_change_photo_order (user_id, photo_id, photo_id_near, is_next);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 18 && !strncmp (key, "change_album_order", 18)) {
    int add = 18, is_next = 0;
    if (!strncmp (key + add, "_next", 5)) {
      is_next = 1;
      add += 5;
    }

    int user_id, album_id, album_id_near, cur;
    if (sscanf (key + add, "%d,%d,%d%n", &user_id, &album_id, &album_id_near, &cur) != 3 || key[cur + add]) {
      RETURN (set, 0);
    }

    int res = do_change_album_order (user_id, album_id, album_id_near, is_next);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 15 && !strncmp (key, "new_", 4) && !strncmp (key + 4, mode_names[mode], 5) && !strncmp (key + 9, "_force", 6)) {
    int user_id, album_id, photo_id, cur, cnt = 1;
    if (sscanf (key + 15, "%d,%d,%d%n,%d%n", &user_id, &album_id, &photo_id, &cur, &cnt, &cur) < 3 || cnt <= 0 || cnt > MAX_PHOTOS || key[cur + 15]) {
      RETURN (set, 0);
    }

    int res = do_create_photo_force (user_id, album_id, cnt, photo_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 15 && !strncmp (key, "new_album_force", 15)) {
    int user_id, album_id, cur;
    if (sscanf (key + 15, "%d,%d%n", &user_id, &album_id, &cur) != 2 || key[cur + 15]) {
      RETURN (set, 0);
    }

    int res = do_create_album_force (user_id, album_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 9 && !strncmp (key, "new_", 4) && !strncmp (key + 4, mode_names[mode], 5)) {
    int user_id, album_id, cur, cnt = 1;
    if (sscanf (key + 9, "%d,%d%n,%d%n", &user_id, &album_id, &cur, &cnt, &cur) < 2 || cnt <= 0 || cnt > MAX_PHOTOS || key[cur + 9]) {
      RETURN (set, 0);
    }

    int res = do_create_photo (user_id, album_id, cnt);

    if (res >= 0) {
      char *ret = dl_pstr ("%d", res);
      return_one_key (c, old_key, ret, strlen (ret));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 9 && !strncmp (key, "new_album", 9)) {
    int user_id, cur;
    if (sscanf (key + 9, "%d%n", &user_id, &cur) != 1 || key[cur + 9]) {
      RETURN (set, 0);
    }

    int res = do_create_album (user_id);

    if (res >= 0) {
      char *ret = dl_pstr ("%d", res);
      return_one_key (c, old_key, ret, strlen (ret));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  if (key_len >= 22 && !strncmp (key, mode_names[mode], 5) && !strncmp (key + 5, "s_overview_albums", 17)) {
    int add = 22, need_reverse = 0, need_count = 0;
    if (!strncmp (key + add, "_reverse", 8)) {
      need_reverse = 1;
      add += 8;
    }
    if (!strncmp (key + add, "_cnt", 4)) {
      need_count = 1;
      add += 4;
    }

    int user_id, offset = MAX_PHOTOS_DYN, limit = -7, cur;
    if (sscanf (key + add, "%d%n#%d%n,%d%n", &user_id, &cur, &offset, &cur, &limit, &cur) < 1 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    if (limit == -7) {
      limit = offset;
      offset = 0;
    }

    key[key_len - 1] = 0;
    char *result = NULL;
    int res = get_photos_overview (user_id, key + add + cur + 1, offset, limit, "", need_reverse, need_count, &result);
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }

  if (key_len >= 15 && !strncmp (key, mode_names[mode], 5) && !strncmp (key + 5, "s_overview", 10)) {
    int add = 15, need_reverse = 0, need_count = 0;
    if (!strncmp (key + add, "_reverse", 8)) {
      need_reverse = 1;
      add += 8;
    }
    if (!strncmp (key + add, "_cnt", 4)) {
      need_count = 1;
      add += 4;
    }

    int user_id, offset = MAX_PHOTOS_DYN, limit = -7, random_tag, cur;
    if (sscanf (key + add, "%d,%d%n#%d%n,%d%n", &user_id, &random_tag, &cur, &offset, &cur, &limit, &cur) < 2 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    if (limit == -7) {
      limit = offset;
      offset = 0;
    }

    message *msg = MESSAGE (c);

    if (msg_verify (msg, random_tag) < 0) {
      RETURN (get, 0);
    }
    if (limit <= 0) {
      if (need_count) {
        limit = 0;
      } else {
        msg_free (msg);
        RETURN (get, 0);
      }
    }

    key[key_len - 1] = 0;
    char *result = NULL;
    int res = get_photos_overview (user_id, msg->text, offset, limit, key + add + cur + 1, need_reverse, need_count, &result);
    key[key_len - 1] = ')';

    if (res != -2) {
      msg_free (msg);
    }
    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }

  if (key_len >= 21 && (!strncmp (key, "in", 2) || !strncmp (key, "de", 2)) && !strncmp (key + 2, "crement_", 8) && !strncmp (key + 10, mode_names[mode], 5) && !strncmp (key + 15, "_field", 6)) {
    int user_id, photo_id, cnt = 1, cur;
    if (sscanf (key + 21, "%d,%d%n,%d%n", &user_id, &photo_id, &cur, &cnt, &cur) < 2 || key[cur + 21] != '(' || key[key_len - 1] != ')') {
      RETURN (set, 0);
    }
    if (key[0] == 'd') {
      cnt = -cnt;
    }

    key[key_len - 1] = 0;
    int res = do_increment_photo_field (user_id, photo_id, key + cur + 22, cnt);
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res == -2 ? -2 : 0);
  }

  if (key_len >= 21 && (!strncmp (key, "in", 2) || !strncmp (key, "de", 2)) && !strncmp (key + 2, "crement_album_field", 19)) {
    int user_id, album_id, cnt = 1, cur;
    if (sscanf (key + 21, "%d,%d%n,%d%n", &user_id, &album_id, &cur, &cnt, &cur) < 2 || key[cur + 21] != '(' || key[key_len - 1] != ')') {
      RETURN (set, 0);
    }
    if (key[0] == 'd') {
      cnt = -cnt;
    }

    key[key_len - 1] = 0;
    int res = do_increment_album_field (user_id, album_id, key + cur + 22, cnt);
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res == -2 ? -2 : 0);
  }

  if (!write_only && key_len >= 12 && !strncmp (key, mode_names[mode], 5) && !strncmp (key + 5, "s_count", 7)) {
    int user_id, album_id, cur;
    if (sscanf (key + 12, "%d,%d%n", &user_id, &album_id, &cur) < 2 || (key[cur + 12] && (key[cur + 12] != '(' || key[key_len - 1] != ')'))) {
      RETURN (get, 0);
    }

    char *condition = NULL;
    if (key[cur + 12] == '(') {
      key[key_len - 1] = 0;
      condition = key + cur + 13;
    }

    int res = get_photos_count (user_id, album_id, condition);
    if (condition != NULL) {
      key[key_len - 1] = ')';
    }

    if (res >= 0) {
      char *ret = dl_pstr ("%d", res);
      return_one_key (c, old_key, ret, strlen (ret));

      RETURN (get, 0);
    }

    RETURN (get, res == -2 ? -2 : 0);
  }

  if (!write_only && key_len >= 12 && !strncmp (key, "albums_count", 12)) {
    int user_id, cur;
    if (sscanf (key + 12, "%d%n", &user_id, &cur) < 1 || (key[cur + 12] && (key[cur + 12] != '(' || key[key_len - 1] != ')'))) {
      RETURN (get, 0);
    }

    char *condition = NULL;
    if (key[cur + 12] == '(') {
      key[key_len - 1] = 0;
      condition = key + cur + 13;
    }

    int res = get_albums_count (user_id, condition);
    if (condition != NULL) {
      key[key_len - 1] = ')';
    }

    if (res >= 0) {
      char *ret = dl_pstr ("%d", res);
      return_one_key (c, old_key, ret, strlen (ret));

      RETURN (get, 0);
    }

    RETURN (get, res == -2 ? -2 : 0);
  }

  if (!write_only && key_len >= 6 && !strncmp (key, mode_names[mode], 5) && !strncmp (key + 5, "s", 1)) {
    int add = 6, need_reverse = 0, need_count = 0;
    if (!strncmp (key + add, "_reverse", 8)) {
      need_reverse = 1;
      add += 8;
    }
    if (!strncmp (key + add, "_cnt", 4)) {
      need_count = 1;
      add += 4;
    }

    int user_id, album_id, offset = MAX_PHOTOS_DYN, limit = -7, cur;
    if (sscanf (key + add, "%d,%d%n#%d%n,%d%n", &user_id, &album_id, &cur, &offset, &cur, &limit, &cur) < 2 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    if (limit == -7) {
      limit = offset;
      offset = 0;
    }

    key[key_len - 1] = 0;
    char *fields = key + add + cur + 1;
    char *condition = strchr (fields, '|');
    if (condition != NULL) {
      *condition++ = 0;
    }

    char *result = NULL;
    int res = get_photos (user_id, album_id, offset, limit, fields, need_reverse, need_count, condition, &result);

    if (condition != NULL) {
      condition[-1] = '|';
    }
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }

  if (!write_only && key_len >= 6 && !strncmp (key, "albums", 6)) {
    int add = 6, need_reverse = 0, need_count = 0;
    if (!strncmp (key + add, "_reverse", 8)) {
      need_reverse = 1;
      add += 8;
    }
    if (!strncmp (key + add, "_cnt", 4)) {
      need_count = 1;
      add += 4;
    }

    int user_id, offset = MAX_ALBUMS, limit = -7, cur;
    if (sscanf (key + add, "%d%n#%d%n,%d%n", &user_id, &cur, &offset, &cur, &limit, &cur) < 1 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    if (limit == -7) {
      limit = offset;
      offset = 0;
    }

    key[key_len - 1] = 0;
    char *fields = key + add + cur + 1;
    char *condition = strchr (fields, '|');
    if (condition != NULL) {
      *condition++ = 0;
    }

    char *result = NULL;
    int res = get_albums (user_id, offset, limit, fields, need_reverse, need_count, condition, &result);

    if (condition != NULL) {
      condition[-1] = '|';
    }
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }

  if (!write_only && key_len >= 5 && !strncmp (key, mode_names[mode], 5)) {
    int add = 5, need_force = 0;
    if (!strncmp (key + add, "_force", 6)) {
      need_force = 1;
      add += 6;
    }

    int user_id, photo_id, cur;
    if (sscanf (key + add, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    key[key_len - 1] = 0;
    char *result = NULL;
    int res = get_photo (user_id, photo_id, need_force, key + add + cur + 1, &result);
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }

  if (!write_only && key_len >= 5 && !strncmp (key, "album", 5)) {
    int add = 5;

    int user_id, album_id, cur;
    if (sscanf (key + add, "%d,%d%n", &user_id, &album_id, &cur) < 2 || key[cur + add] != '(' || key[key_len - 1] != ')') {
      RETURN (get, 0);
    }

    key[key_len - 1] = 0;
    char *result = NULL;
    int res = get_album (user_id, album_id, 0, key + add + cur + 1, &result);
    key[key_len - 1] = ')';

    if (res > 0) {
      return_one_key_flags (c, old_key, result, strlen (result), 1);

      RETURN (get, 0);
    }

    RETURN (get, res);
  }


  if (key_len >= 13 && !strncmp (key, "restore_", 8) && !strncmp (key + 8, mode_names[mode], 5)) {
    int user_id, photo_id, cur;
    if (sscanf (key + 13, "%d,%d%n", &user_id, &photo_id, &cur) < 2 || key[cur + 13]) {
      RETURN (set, 0);
    }

    int res = do_restore_photo (user_id, photo_id);

    if (res > 0) {
      return_one_key (c, old_key, OK, strlen (OK));

      RETURN (set, 0);
    }

    RETURN (set, res);
  }

  RETURN (get, 0);
}