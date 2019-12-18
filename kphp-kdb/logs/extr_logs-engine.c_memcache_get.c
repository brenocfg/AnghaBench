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
struct TYPE_4__ {char* text; int len; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int FN ; 
 int /*<<< orphan*/  GET_LOG ; 
 int /*<<< orphan*/  INIT ; 
 int MAX_HISTORY ; 
 int MAX_VALUE_LEN ; 
 TYPE_1__* MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_LOG_VERBOSITY ; 
 int STATS_BUFF_SIZE ; 
 char* buf ; 
 double cputime () ; 
 char* dl_pstr (char*,int) ; 
 char* do_add_field (char*) ; 
 char* do_create_type (char*) ; 
 scalar_t__ do_set_color (int,long long,int,int,int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,double) ; 
 int /*<<< orphan*/  get ; 
 int get_color (int,long long) ; 
 int get_time () ; 
 char* get_type_size (int) ; 
 char* get_types () ; 
 int history_l ; 
 char** history_q ; 
 int /*<<< orphan*/  history_q_add (char*) ; 
 int history_r ; 
 int logs_prepare_stats () ; 
 char* logs_select (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ msg_verify (TYPE_1__*,int) ; 
 int prepare_stats (struct connection*,char*,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*,...) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ test_mode ; 
 int verbosity ; 
 int /*<<< orphan*/  write_only ; 

int memcache_get (struct connection *c, const char *old_key, int old_key_len) {
  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = logs_prepare_stats();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }

  GET_LOG;

  SET_LOG_VERBOSITY;

  INIT;

  if (!write_only && key_len >= 6 && !strncmp (key, "SELECT", 6) && key_len + 1 < STATS_BUFF_SIZE) {
    memcpy (stats_buff, key, key_len);
    stats_buff[key_len] = 0;
    int i;
    for (i = 0; i < key_len; i++) {
      if (stats_buff[i] == (char)0xa0) {
        stats_buff[i] = ' ';
      }
    }

    double tt = 0.0;
    if (test_mode) {
      tt = -cputime();
    }

    history_q_add (stats_buff);

    char *res = logs_select (stats_buff, key_len);

    return_one_key (c, old_key, res, strlen (res));

    if (test_mode) {
      tt += cputime();
      if (tt >= 0.01) {
        fprintf (stderr, "query %s total time : %.6lf\n\n", history_q[(history_r + MAX_HISTORY - 1) % MAX_HISTORY], tt);
      }
    }

    RETURN(get, 0);
  }

  if (!write_only && key_len >= 6 && !strncmp (key, "select", 6)) {
    int random_tag;
    if (sscanf (key, "select%d", &random_tag) != 1) {
      RETURN(get, 0);
    }
    message *msg = MESSAGE(c);

    if (msg_verify (msg, random_tag) < 0) {
      RETURN(get, 0);
    }

    double tt = 0.0;
    if (test_mode) {
      tt = -cputime();
    }

    history_q_add (msg->text);

    memcpy (buf, msg->text, msg->len + 1);

    char *res = logs_select (buf, msg->len);

    return_one_key (c, old_key, res, strlen (res));

    if (test_mode) {
      tt += cputime();
      if (tt >= 0.01) {
        fprintf (stderr, "query %s total time : %.6lf\n\n", stats_buff, tt);
      }
    }

    RETURN(get, 0);
  }

  if (key_len >= 11 && !strncmp (key, "create_type", 11)) {
    const char *s = key + 11;
    int sn = key_len - 11;
    if (sn >= 2 && s[0] == '(' && s[sn - 1] == ')') {
      memcpy (buf, s + 1, sn - 2);
      buf[sn - 2] = 0;

      char *res = do_create_type (buf);
      return_one_key (c, old_key, res, strlen (res));
    }

    RETURN(set, 0);
  }

  if (key_len >= 9 && !strncmp (key, "add_field", 9)) {
    const char *s = key + 9;
    int sn = key_len - 9;
    if (sn >= 2 && s[0] == '(' && s[sn - 1] == ')') {
      memcpy (buf, s + 1, sn - 2);
      buf[sn - 2] = 0;

      char *res = do_add_field (buf);
      return_one_key (c, old_key, res, strlen (res));
    }

    RETURN(set, 0);
  }

  if (!write_only && key_len >= 9 && !strncmp (key, "type_size", 9)) {
    int type;
    if (sscanf (key + 9, "%d", &type) != 1) {
      type = -1;
    } else if (type == -1) {
      return_one_key (c, old_key, "", 0);
      return 0;
    }

    char *res = get_type_size (type);

    return_one_key (c, old_key, res, strlen (res));
    return 0;
  }

  if (!write_only && key_len >= 5 && !strncmp (key, "color", 5)) {
    int field_num;
    long long field_value;
    int cur;
    if (sscanf (key + 5, "%d,%lld%n", &field_num, &field_value, &cur) != 2 || field_num < 0 || field_num >= FN || cur + 5 != key_len) {
      return 0;
    }

    char *res = dl_pstr ("%d", get_color (field_num, field_value));

    return_one_key (c, old_key, res, strlen (res));
    return 0;
  }

  if (key_len >= 12 && !strncmp (key, "change_color", 12)) {
    int field_num;
    long long field_value;
    int and_mask;
    int xor_mask;
    int cnt = 1;
    int cur;

    if (sscanf (key + 12, "%d,%lld,%d,%d%n#%d%n", &field_num, &field_value, &and_mask, &xor_mask, &cur, &cnt, &cur) < 4 || field_num < 0 || field_num >= FN || cur + 12 != key_len) {
      return 0;
    }

    char *res = do_set_color (field_num, field_value, cnt, and_mask, xor_mask) ? "OK" : "NOK";

    return_one_key (c, old_key, res, strlen (res));
    return 0;
  }

  if (!write_only && key_len == 5 && !strcmp (key, "types")) {
    char *res = get_types();

    return_one_key (c, old_key, res, strlen (res));
    return 0;
  }

  if (!write_only && key_len == 4 && !strcmp (key, "time")) {
    int c_time = get_time();
    char *res = dl_pstr ("%d", c_time);

    return_one_key (c, old_key, res, strlen (res));
    return 0;
  }

  if (!write_only && key_len >= 7 && !strncmp (key, "history", 7)) {
    int cnt;
    if (sscanf (key + 7, "%d", &cnt) != 1) {
      cnt = MAX_HISTORY;
    }

    char *res = buf;
    int cur = history_r;

    while (cnt-- && cur != history_l) {
      cur--;
      if (cur == -1) {
        cur += MAX_HISTORY + 1;
      }
      int l = strlen (history_q[cur]);
      if (res - buf + l + 2 >= MAX_VALUE_LEN) {
        break;
      }
      memcpy (res, history_q[cur], l);
      res += l;
      *res++ = '\n';
    }
    *res++ = 0;

    return_one_key (c, old_key, buf, strlen (buf));
    return 0;
  }

  return 0;
}