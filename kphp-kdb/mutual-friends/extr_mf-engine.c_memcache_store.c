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
 int /*<<< orphan*/  INIT ; 
 int MAX_FRIENDS ; 
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int active_aio_queries ; 
 int add_common_friends (int,int,int*,int) ; 
 char* buf ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 int* fr_buff ; 
 int get_int (char const**) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_store (struct connection *c, int op, const char *old_key, int old_key_len, int flags, int delay, int size) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d, \n", old_key, old_key_len, size);
  }

  if (size + 1 < MAX_VALUE_LEN) {
    char *key;
    int key_len;

    eat_at (old_key, old_key_len, &key, &key_len);

    //add("common_friends$id[,$add]", "$n,$f1,...,$fn")
    if (key_len >= 14 && !strncmp (key, "common_friends", 14)) {
      int uid;
      int add;
      int t = sscanf (key + 14, "%d,%d\n", &uid, &add);

      //TODO: comment for testing
      if (add != -1 && add != -4 && add != 1 && add != 4) {
        active_aio_queries |= (1 << 18);
        RETURN(set, -2);
      }

      if (t != 1 && t != 2) {
        RETURN(set, -2);
      }
      if (t == 1) {
        add = 1;
      }

      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      const char *s = buf;
      int n = get_int (&s), i;

      if (n >= MAX_FRIENDS - 1) {
        active_aio_queries |= (1 << 15);
        RETURN(set, 0);
      }

      if (n < 0) {
        active_aio_queries |= (1 << 16);
        RETURN(set, 0);
      }

      for (i = 0; i < n; i++)
      {
        if (*s == 0) {
          RETURN(set, 0);
        }
        s++;
        fr_buff[i] = get_int (&s);
        if (fr_buff[i] <= 0 || fr_buff[i] >= (1 << 28)) {
          active_aio_queries |= (1 << 17);
          RETURN(set, 0);
        }
      }

      int res = add_common_friends (uid, add, fr_buff, n);
      RETURN(set, res);
    }
  }

  RETURN(set, -2);
}