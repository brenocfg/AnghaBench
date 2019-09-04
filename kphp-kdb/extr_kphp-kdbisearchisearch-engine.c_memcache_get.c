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
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  MAX_VALUE_LEN ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  black_list_force () ; 
 char* black_list_get () ; 
 char* buf ; 
 double cmd_time ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  get ; 
 int /*<<< orphan*/  get_best (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hints (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_suggestion (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_top (char*,int,int /*<<< orphan*/ ) ; 
 int isearch_prepare_stats () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 double mytime () ; 
 int prepare_stats (struct connection*,char*,scalar_t__) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,char*,int) ; 
 int sscanf (char*,char*,int*) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *old_key, int old_key_len) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s', key_len=%d\n", old_key, old_key_len);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  int mode = 0, st = 0;

  if (key_len >= 5 && !strncmp (key, "hints", 5)) {
    mode = 1;
    st = 5;
  }

#ifdef TYPES
  if (key_len >= 5 && !strncmp (key, "types", 5)) {
    mode = 2;
    st = 5;
  }

  if (key_len >= 11 && !strncmp (key, "hints_debug", 11)) {
    mode = 3;
    st = 11;
  }
#endif

  if (mode) {
    if (key[st] != '(' || key[key_len - 1] != ')') {
      RETURN(get, 0);
    }
    int len = key_len - st - 2;
    memcpy (buf, key + st + 1, sizeof (char) * len);
    buf[len] = 0;

    if (verbosity >= 2) {
      fprintf (stderr, "run get_hints (%s, %d)\n", buf, mode);
    }

    get_hints (buf, mode, MAX_VALUE_LEN);

    return_one_key (c, old_key, buf, strlen (buf));

    if (verbosity > 0) {
      if (mytime() + cmd_time > 0.005) {
        fprintf (stderr, "Warning!!! Search query (%s) was %lf seconds.\n", key, mytime() + cmd_time);
      }
    }

    RETURN(get, 0);
  }

  if (key_len >= 10 && !strncmp (key, "suggestion", 10)) {
    if (key[10] != '(' || key[key_len - 1] != ')') {
      RETURN(get, 0);
    }

    int len = key_len - 12;
    memcpy (buf, key + 11, sizeof (char) * len);
    buf[len] = 0;

    if (verbosity >= 2) {
      fprintf (stderr, "run get_suggestion (%s)\n", buf);
    }

    get_suggestion (buf, MAX_VALUE_LEN);

    return_one_key (c, old_key, buf, strlen (buf));

    if (verbosity > 0) {
      if (mytime() + cmd_time > 0.005) {
        fprintf (stderr, "Warning!!! Search query (%s) was %lf seconds.\n", key, mytime() + cmd_time);
      }
    }

    RETURN(get, 0);
  }

  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int len = isearch_prepare_stats ();
    int len2 = prepare_stats (c, stats_buff + len, STATS_BUFF_SIZE - len);
    return_one_key (c, old_key, stats_buff, len + len2 - 1);

    return 0;
  }

  if (key_len >= 3 && !strncmp (key, "top", 3)) {
    int cnt;
    if (sscanf (key, "top%d", &cnt) == 1) {
      get_top (buf, cnt, MAX_VALUE_LEN);

      return_one_key (c, old_key, buf, strlen (buf));
    }
    RETURN(get, 0);
  }

  if (key_len >= 4 && !strncmp (key, "best", 4)) {
    int cnt;
    if (sscanf (key, "best%d", &cnt) == 1) {
      get_best (buf, cnt, MAX_VALUE_LEN);

      return_one_key (c, old_key, buf, strlen (buf));
    }
    RETURN(get, 0);
  }

  if (key_len >= 10 && !strncmp (key, "black_list", 10)) {
    if (key_len >= 16 && !strncmp (key, "black_list_force", 16)) {
      black_list_force();
    } else {
      char *s = black_list_get();
      int len = strlen (s);

      return_one_key (c, old_key, s, len);
    }

    RETURN(get, 0);
  }

  RETURN(get, 0);
}