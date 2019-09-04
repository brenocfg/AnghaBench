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
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RES ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atol (scalar_t__*) ; 
 int binlog_disabled ; 
 int do_add_friend (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ do_add_friend_request (int,int,int /*<<< orphan*/ ,int) ; 
 int do_set_category_friend_list (int,int,int /*<<< orphan*/ ,int) ; 
 int do_set_privacy (int,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int exec_store_userlist (struct connection*,char const*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int mct_add ; 
 int mct_set ; 
 int parse_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ parse_privacy_key (char const*,int /*<<< orphan*/ *,int) ; 
 int read_in (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__ reverse_friends_mode ; 
 int sscanf (char const*,char*,int*,int*) ; 
 scalar_t__* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ verbosity ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  int user_id, cat = 0, friend_id = 0, i;
  privacy_key_t privacy_key = 0;

  if (verbosity > 0) {
    fprintf (stderr, "mc_store: op=%d, key=\"%s\", flags=%d, delay=%d, bytes=%d\n", op, key, flags, delay, size);
  }

  if (binlog_disabled == 2) {
    return -2;
  }

  if (reverse_friends_mode) {
    if (op == mct_set && key_len >= 8 && !strncmp (key, "userlist", 8)) {
      return exec_store_userlist (c, key, key_len, size);
    }
    return 0;
  }

  if (op == mct_set && sscanf (key, "friends%d_%d", &user_id, &cat) == 2 && user_id > 0 && cat > 0 && cat < 32) {
    int s = parse_list (R, MAX_RES, &c->In, size);
    int res = 0;
    if (s >= 0) {
      res = do_set_category_friend_list (user_id, cat, R, s);
    }
    if (verbosity > 0) {
      fprintf (stderr, "set friend cat list: size = %d, res = %d\n", s, res);
    }
    return res;
  }

  if (size > 1024) {
    return -2;
  }

  assert (read_in (&c->In, stats_buff, size) == size);
  stats_buff[size] = 0;

  if (sscanf (key, "friendreq%d_%d", &user_id, &friend_id) == 2 && user_id > 0 && friend_id > 0) {
    return do_add_friend_request (user_id, friend_id, atol(stats_buff), (op == mct_add) * 2 + (op == mct_set)) >= 0;
  }

  if (op != mct_add && sscanf (key, "friend%d_%d", &user_id, &friend_id) == 2 && user_id > 0 && friend_id > 0) {
    return do_add_friend (user_id, friend_id, atol(stats_buff), 0, op == mct_set);
  }

  if (op != mct_add && sscanf (key, "privacy%d_%n", &user_id, &i) >= 1 && user_id > 0 && parse_privacy_key (key+i, &privacy_key, 1) > 0) {
    return do_set_privacy (user_id, privacy_key, stats_buff, size, op == mct_set);
  }

  return 0;
}