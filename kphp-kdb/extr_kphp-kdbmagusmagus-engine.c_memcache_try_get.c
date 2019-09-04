#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_4__ {char* text; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LOG ; 
 int /*<<< orphan*/  INIT ; 
 TYPE_1__* MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOG_VERBOSITY ; 
 scalar_t__ STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ buf ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  get ; 
 int get_objs (int,int,int,scalar_t__) ; 
 int get_objs_hints (int,int,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  hst (char*,char const*,int) ; 
 int magus_prepare_stats () ; 
 scalar_t__ msg_verify (TYPE_1__*,int) ; 
 int prepare_stats (struct connection*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,scalar_t__,int) ; 
 int sscanf (char*,char*,int*,int*,...) ; 
 scalar_t__ stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_try_get (struct connection *c, const char *old_key, int old_key_len) {
  hst ("memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);

  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = magus_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }

  GET_LOG;

  SET_LOG_VERBOSITY;

  INIT;

  if (key_len >= 5 && !strncmp (key, "hints", 5)) {
    int random_tag, cur_add;
    int fn, user_id, type;
    message *msg = MESSAGE(c);

    if (sscanf (key, "hints%d%n", &random_tag, &cur_add) != 1 || msg_verify (msg, random_tag) < 0 || cur_add < key_len) {
      RETURN(get, 0);
    }

    char *s = msg->text;
    int cur = 0;
    cur_add = 0;

    assert (s != NULL);

    if (sscanf (s, "%d,%d,%d%n", &user_id, &type, &fn, &cur_add) != 3 || fn <= 0) {
      RETURN(get, 0);
    }
    cur += cur_add;

    int res = get_objs_hints (user_id, type, fn, s + cur, buf);

    if (res >= 0) {
      return_one_key (c, old_key, buf, strlen (buf));
      RETURN(get, 0);
    }

    RETURN(get, res);
  }

  if (key_len >= 10 && !strncmp (key, "apps_hints", 10)) {
    int fn, user_id;
    int cur = 10, cur_add;
    if (sscanf (key + cur, "%d,%d%n", &user_id, &fn, &cur_add) != 2 || fn <= 0) {
      RETURN(get, 0);
    }
    cur += cur_add;

    int res = get_objs_hints (user_id, 41, fn, key + cur, buf);

    if (res >= 0) {
      return_one_key (c, old_key, buf, strlen (buf));
      RETURN(get, 0);
    }

    RETURN(get, res);
  }

  if (key_len >= 4 && !strncmp (key, "apps", 4)) {
    int user_id, cnt, cur_add;
    if (sscanf (key, "apps%d#%d%n", &user_id, &cnt, &cur_add) != 2 || cnt <= 0 || key[cur_add]) {
      RETURN(get, 0);
    }

    int res = get_objs (user_id, 41, cnt, buf);

    if (res >= 0) {
      return_one_key (c, old_key, buf, strlen (buf));
      RETURN(get, 0);
    }

    RETURN(get, res);
  }

  RETURN(get, 0);
}