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
struct TYPE_5__ {int /*<<< orphan*/  text; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LOG ; 
 int /*<<< orphan*/  INIT ; 
 int MAX_RES ; 
 TYPE_1__* MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_LOG_VERBOSITY ; 
 scalar_t__ STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  delete ; 
 int do_delete_answer (int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  get ; 
 char* get_answer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hst (char*,char const*,int) ; 
 int /*<<< orphan*/  msg_free (TYPE_1__*) ; 
 scalar_t__ msg_verify (TYPE_1__*,int) ; 
 int prepare_stats (struct connection*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,scalar_t__,int) ; 
 int /*<<< orphan*/  return_one_key_flags (struct connection*,char const*,char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*,int*,...) ; 
 scalar_t__ stats_buff ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int support_prepare_stats () ; 

int memcache_get (struct connection *c, const char *old_key, int old_key_len) {
  hst ("memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);

  char *key;
  int key_len;
  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = support_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }

  GET_LOG;

  SET_LOG_VERBOSITY;

  INIT;

  if (key_len >= 6 && !strncmp (key, "answer", 6)) {
    int add = 6, debug = 0;
    if (!strncmp (key + 6, "_debug", 6)) {
      debug = 1;
      add += 6;
    }
    int user_id, agent_id, random_tag, cur, cnt = MAX_RES;
    if (sscanf (key + add, "%d,%d,%d%n#%d%n", &user_id, &agent_id, &random_tag, &cur, &cnt, &cur) < 3 || key[add + cur]) {
      RETURN (get, 0);
    }
    message *msg = MESSAGE (c);

    if (msg_verify (msg, random_tag) < 0 || cnt <= 0) {
      msg_free (msg);
      RETURN (get, 0);
    }

    char *res = get_answer (user_id, agent_id, msg->len, msg->text, cnt, debug);

    if (res != NULL) {
      return_one_key_flags (c, old_key, res, strlen (res), 1);
    }

    msg_free (msg);
    RETURN (get, 0);
  }

  if (key_len >= 13 && !strncmp (key, "delete_answer", 13)) {
    int add = 13;
    int user_id, cur;
    if (sscanf (key + add, "%d%n", &user_id, &cur) < 1 || key[add + cur]) {
      RETURN (delete, 0);
    }

    int res = do_delete_answer (user_id);

    if (res) {
      return_one_key_flags (c, old_key, "DELETED", strlen ("DELETED"), 1);
    }

    RETURN (delete, 0);
  }

  RETURN (delete, 0);
}