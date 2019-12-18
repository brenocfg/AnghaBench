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
 scalar_t__ COMM_MODE ; 
 scalar_t__ NOTIFY_MODE ; 
 scalar_t__ RECOMMEND_MODE ; 
 scalar_t__ UG_MODE ; 
 scalar_t__ check_split (int) ; 
 int do_add_del_bookmark (int,int,int,int,int) ; 
 int exec_get_notification_updates (struct connection*,char const*,int,int) ; 
 int exec_get_raw_comm_updates (struct connection*,char const*,int,int) ; 
 int exec_get_raw_notification_updates (struct connection*,char const*,int,int) ; 
 int exec_get_raw_recommend_updates (struct connection*,char const*,int,int) ; 
 int exec_get_raw_updates (struct connection*,char const*,int,int) ; 
 int exec_get_raw_user_comm_bookmarks (struct connection*,char const*,int,int) ; 
 int exec_get_raw_user_comm_updates (struct connection*,char const*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int get_at_prefix_length (char const*,int) ; 
 int get_privacy_mask (int) ; 
 int get_recommend_rate (int,int,double*) ; 
 int news_prepare_stats (struct connection*) ; 
 int news_wait (struct connection*) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int sprintf (char*,char*,double) ; 
 int sscanf (char const*,char*,int*,...) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  int dog_len = get_at_prefix_length (key, key_len);
  key += dog_len;
  key_len -= dog_len;
  int user_id, res = 0;

  if (key_len >= 11 && UG_MODE && (!strncmp (key, "raw_updates", 11) || !strncmp (key, "%raw_updates", 12))) {
    res = exec_get_raw_updates (c, key, key_len, dog_len);
    free_tmp_buffers (c);
    return res;
  }

  if (key_len >= 16 && COMM_MODE && (!strncmp (key, "raw_comm_updates", 16) || !strncmp (key, "%raw_comm_updates", 17))) {
    res = exec_get_raw_comm_updates (c, key, key_len, dog_len);
    free_tmp_buffers (c);
    return res;
  }

  if (key_len >= 21 && RECOMMEND_MODE && (!strncmp (key, "raw_recommend_updates", 21) || !strncmp (key, "%raw_recommend_updates", 22))) {
    res = exec_get_raw_recommend_updates (c, key, key_len, dog_len);
    free_tmp_buffers (c);
    return res;
  }
  free_tmp_buffers (c);

  if (key_len >= 21 && COMM_MODE && (!strncmp (key, "raw_user_comm_updates", 21) || !strncmp (key, "%raw_user_comm_updates", 22))) {
    res = exec_get_raw_user_comm_updates (c, key, key_len, dog_len);
    if (res < 0) {
      res = news_wait (c);
      return 0;
    }
    return res;
  }

  if (key_len >= 23 && COMM_MODE && (!strncmp (key, "raw_user_comm_bookmarks", 23) || !strncmp (key, "%raw_user_comm_bookmarks", 24))) {
    res = exec_get_raw_user_comm_bookmarks (c, key, key_len, dog_len);
    if (res < 0) {
      res = news_wait (c);
      return 0;
    }
    return res;
  }

  if (key_len >= 25 && NOTIFY_MODE && (!strncmp (key, "raw_notification_updates", 24) || !strncmp (key, "%raw_notification_updates", 25))) {
    res = exec_get_raw_notification_updates (c, key, key_len, dog_len);
    return res;
  }

  if (key_len >= 21 && NOTIFY_MODE && !strncmp (key, "notification_updates", 20)) {
    res = exec_get_notification_updates (c, key, key_len, dog_len);
    return res;
  }


  if (UG_MODE && sscanf (key, "mask%d", &user_id) == 1) {
    res = get_privacy_mask (user_id);
    if (verbosity > 1) {
      fprintf (stderr, "get_privacy(%d) = %d\n", user_id, res);
    }
    if (res >= 0) {
      return return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%d", res));
    }
  }

  if (COMM_MODE && !strncmp (key, "add_bookmark", 12)) {
    int type, owner, place;
    if (sscanf (key, "add_bookmark_%d_%d_%d:%d", &type, &owner, &place, &user_id) == 4) {
      int res = 0;
      if (check_split (owner) || check_split (place)) {
        res = do_add_del_bookmark (user_id, type, owner, place, 1);
      }
      return return_one_key (c, key - dog_len, res ? "1" : "0", 1);
    }
  }

  if (COMM_MODE && !strncmp (key, "del_bookmark", 12)) {
    int type, owner, place;
    if (sscanf (key, "del_bookmark_%d_%d_%d:%d", &type, &owner, &place, &user_id) == 4) {
      int res = 0;
      if (check_split (owner) || check_split (place)) {
        res = do_add_del_bookmark (user_id, type, owner, place, 0);
      }
      return return_one_key (c, key - dog_len, res ? "1" : "0", 1);
    }
  }

  if (RECOMMEND_MODE && !strncmp (key, "recommend_rate", 14))  {
    int type, action;
    if (sscanf (key + 14, "%d,%d", &type, &action) == 2) {
      double rate;
      int res = get_recommend_rate (type, action, &rate);
      if (!res) {
        return return_one_key (c, key - dog_len, stats_buff, sprintf (stats_buff, "%.10lf", rate));
      }
    }
  }

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int stats_len = news_prepare_stats (c);
    return return_one_key (c, key - dog_len, stats_buff, stats_len);
  }
  return 0;
}