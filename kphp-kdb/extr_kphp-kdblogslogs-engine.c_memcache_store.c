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
 int FN ; 
 int /*<<< orphan*/  INIT ; 
 int MAX_QUERY_LEN ; 
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (char*) ; 
 char* buf ; 
 int do_add_event (char*,int*,char*) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* msg_get_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_reinit (int /*<<< orphan*/ ,int,int) ; 
 int read_long (char const*,long long*,int*) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*) ; 
 char* stats_buff ; 
 scalar_t__* std_t ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_only ; 

int memcache_store (struct connection *c, int op, const char *old_key, int old_key_len, int flags, int delay, int size) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d\n", old_key, old_key_len, size);
  }

  if (size + 1 < MAX_VALUE_LEN) {
    char *key;
    int key_len;

    eat_at (old_key, old_key_len, &key, &key_len);

    if (!write_only && key_len >= 6 && !strncmp (key, "select", 6) && size < MAX_QUERY_LEN) {
      int random_tag;
      if (sscanf (key, "select%d", &random_tag) != 1) {
        RETURN(set, -2);
      }

      if (verbosity > 1) {
        fprintf (stderr, "current_text %d\n", random_tag);
      }

      if (msg_reinit (MESSAGE(c), size, random_tag) < 0) {
        fprintf (stderr, "WARNING: not enough memory for message allocating\n");
        RETURN(set, -2); // not_enough memory
      }

      char *s = msg_get_buf (MESSAGE(c));
      assert (s);
      safe_read_in (&c->In, s, size);
      s[size] = 0;

      RETURN(set, 1);
    }

    if (key_len >= 9 && !strncmp (key, "add_event", 9) && key_len < 1000) {
      const char *s = key + 9;
      int sn = key_len - 9;
      if (s[0] != '(' || s[sn - 1] != ')')  {
        RETURN(set, -2);
      }
      s++, sn -= 2;
      int i;
      char *ts = stats_buff;

      if (verbosity > 2) {
        fprintf (stderr, "%d : %s\n", sn, s);
      }
      for (i = 0; i < sn && s[i] != ','; i++) {
        *ts++ = s[i];
      }
      *ts = 0;

      if (verbosity > 2 && i != sn) {
        fprintf (stderr, "key = %s | ts = %s, s = %s\n", key, stats_buff, s + i + 1);
      }

      int params[FN - 2];
      int j;
      for (j = 2; j < FN; j += 1 + std_t[j]) {
        int pos = -1;
        long long x;
        if (read_long (s + i + 1, &x, &pos) < 1 || (i + 1 + pos != sn && s[pos + i + 1] != ',')) {
          RETURN(set, -2);
        }

        i += pos + 1;
        if (std_t[j]) {
          *(long long *)&params[j - 2] = x;
        } else {
          params[j - 2] = (int)x;
        }
      }

      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      int result = do_add_event (stats_buff, params, buf);

      RETURN(set, result);
    }
  }

  RETURN(set, -2);
}