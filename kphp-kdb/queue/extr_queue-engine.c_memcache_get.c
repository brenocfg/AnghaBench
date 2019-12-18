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
struct TYPE_4__ {char* name; int ref_cnt; int ev_first; int keys_cnt; int subscr_cnt; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  qkey ;
typedef  int ll ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LOG ; 
 int KEY_LEN ; 
 int /*<<< orphan*/  LOG_HISTORY ; 
 int /*<<< orphan*/  QRETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_DEF ; 
 int /*<<< orphan*/  SET_LOG_VERBOSITY ; 
 int STATS_BUFF_SIZE ; 
 char* buf ; 
 int /*<<< orphan*/  cmd_get ; 
 int /*<<< orphan*/  dl_log_add (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  get ; 
 char* get_events_http (int /*<<< orphan*/ *) ; 
 char* get_news_key (int,long long,int,int) ; 
 TYPE_1__* get_queue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_queue_alias (char*,int*) ; 
 TYPE_1__* get_queue_by_alias (int) ; 
 int /*<<< orphan*/  get_queue_news_alias (int,int*) ; 
 char* get_timestamp_key (char*,int,long long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* get_watchcat_key (char*,int,long long,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 double mytime () ; 
 int prepare_stats (struct connection*,char*,int) ; 
 int /*<<< orphan*/  query ; 
 int queue_prepare_stats () ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int sscanf (char*,char*,int*,...) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  upd_secret (int) ; 
 int /*<<< orphan*/ * validate_key (char*,int,long long,int,int /*<<< orphan*/ ,char*) ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *old_key, int old_key_len) {
  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  }
  dl_log_add (LOG_HISTORY, 1, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  sprintf (query, "key='%s', key_len=%d", old_key, old_key_len);

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = queue_prepare_stats();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);

    return_one_key (c, old_key, stats_buff, len + len2 - 1);
    return 0;
  }

  GET_LOG;

  SET_LOG_VERBOSITY;

  double cmd_time = -mytime();
  cmd_get++;

  if (key_len >= 13 && !strncmp (key, "timestamp_key", 13)) {
    int id, timeout, st;
    long long ip;
    if (sscanf (key, "timestamp_key%d,%lld,%d%n", &id, &ip, &timeout, &st) == 3 && key[st] == '(' && key[key_len - 1] == ')' && key_len - st - 2 < STATS_BUFF_SIZE) {
      char *s = stats_buff;
      int len = key_len - st - 2;
      memcpy (s, key + st + 1, len);
      s[len] = 0;
      dl_log_add (LOG_HISTORY, 1, "GET KEY (%s) id = %d, ip = %lld\n", s, id, ip);
      s = get_timestamp_key (s, id, ip, timeout, NULL, Q_DEF);
      return_one_key (c, old_key, s, strlen (s));
    }

    QRETURN(get, 0);
  }

  if (key_len >= 5 && !strncmp (key, "alias", 5)) {
    int st = 5, is_news = 0;
    if (key_len >= 10 && !strncmp (key + 5, "_news", 5)) {
      st += 5;
      is_news = 1;
    }
    if (key[st] == '(' && key[key_len - 1] == ')' && key_len - st - 2 < STATS_BUFF_SIZE) {
      char *s = stats_buff;
      int len = key_len - st - 2;
      memcpy (s, key + st + 1, len);
      s[len] = 0;
      dl_log_add (LOG_HISTORY, 1, "GET ALIAS (%s)\n", s);

      ll res;
      if (is_news) {
        ll id;
        if (sscanf (s, "%lld", &id) != 1 || !get_queue_news_alias (id, &res)) {//TODO get alias_news(1qwerty)
          QRETURN(get, 0);
        }
      } else {
        if (!is_news && !get_queue_alias (s, &res)) {
          QRETURN(get, 0);
        }
      }

      sprintf (s, "%lld", res);

      return_one_key (c, old_key, s, strlen (s));
    }

    QRETURN(get, 0);
  }

  if (key_len >= 14 && !strncmp (key, "qname_by_alias", 14)) {
    ll id;
    int st;
    if (sscanf (key, "qname_by_alias%lld%n", &id, &st) == 1 && key[st] == 0) {
      queue *q = get_queue_by_alias (id);
      if (q != NULL) {
        sprintf (buf, "%s : ref_cnt = %d, ev_first = %p, keys_cnt = %d, subscr_cnt = %d", q->name, q->ref_cnt, q->ev_first, q->keys_cnt, q->subscr_cnt);
        return_one_key (c, old_key, buf, strlen (buf));
      }
    }

    QRETURN(get, 0);
  }

  if (key_len >= 10 && !strncmp (key, "queue_info", 10)) {
    if (key[10] == '(' && key[key_len - 1] == ')') {
      key[key_len - 1] = 0;
      char *qname = key + 11;
      queue *q = get_queue (qname, 0);
      if (q != NULL) {
        sprintf (buf,
          "name\t%s\n"
          "ref_cnt\t%d\n"
          "key_cnt\t%d\n"
          "subscr_cnt\t%d\n"
          "ev_frist\t%p\n"
          , q->name, q->ref_cnt, q->keys_cnt, q->subscr_cnt, q->ev_first);
        return_one_key (c, old_key, buf, strlen (buf));
      }
    }
    QRETURN (get, 0);
  }

  if (key_len >= 12 && !strncmp (key, "watchcat_key", 12)) {
    int id, timeout, st;
    long long ip;
    if (sscanf (key, "watchcat_key%d,%lld,%d%n", &id, &ip, &timeout, &st) == 3 && key[st] == '(' && key[key_len - 1] == ')' && key_len - st - 2 < STATS_BUFF_SIZE) {
      char *s = stats_buff;
      int len = key_len - st - 2;
      memcpy (s, key + st + 1, len);
      s[len] = 0;

      char *tmp = s;
      while (*tmp) {
        if (*tmp == '?') {
          *tmp = 0x1f;
        }
        tmp++;
      }

      s = get_watchcat_key (s, id, ip, timeout);
      if (s != NULL) {
        return_one_key (c, old_key, s, strlen (s));
      }
    }

    QRETURN(get, 0);
  }

  if (key_len >= 8 && !strncmp (key, "news_key", 8)) {
    int id, timeout;
    long long ip;
    ll uid;
    if (sscanf (key, "news_key%d,%lld,%d(%lld)", &id, &ip, &timeout, &uid) == 4) {
      char *s;
      dl_log_add (LOG_HISTORY, 1, "GET NEWS KEY (%lld) id = %d, ip = %lld\n", uid, id, ip);
      s = get_news_key (id, ip, timeout, uid);
      if (s != NULL) {
        return_one_key (c, old_key, s, strlen (s));
      }
    }

    QRETURN(get, 0);
  }

  if (key_len >= 5 && !strncmp (key, "queue", 5)) {
    int id, ts, st;
    long long ip;
    if (sscanf (key, "queue%d,%lld,%d%n", &id, &ip, &ts, &st) == 3 && key[st] == '(' && key[key_len - 1] == ')' && key_len - st - 2 < STATS_BUFF_SIZE) {
      char *s = stats_buff, *ans = "{\"failed\":2}";
      int len = key_len - st - 2;

      if (len == KEY_LEN) {
        memcpy (s, key + st + 1, len);
        s[len] = 0;

        qkey *k;

        //fprintf (stderr, "mc validate : %s %d %lld %d\n", s, id, ip, ts);

        char err;
        if ((k = validate_key (s, id, ip, ts, 0, &err)) != NULL) {
          ans = get_events_http (k);
        }
      }

      return_one_key (c, old_key, ans, strlen (ans));
    }

    QRETURN(get, 0);
  }

  if (key_len >= 10 && !strncmp (key, "upd_secret", 10)) {
    int id;
    if (sscanf (key, "upd_secret%d", &id) == 1) {
      upd_secret (id);
    }
    return_one_key (c, old_key, "OK", 2);

    QRETURN(get, 0);
  }


  QRETURN(get, 0);
}