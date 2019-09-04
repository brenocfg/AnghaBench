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
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  MESSAGE (struct connection*) ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 char* buf ; 
 int do_add_exception (int,int,char*) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hst (char*,char const*,int,int) ; 
 char* msg_get_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_reinit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 

int memcache_store (struct connection *c, int op, const char *old_key, int old_key_len, int flags, int delay, int size) {
  INIT;

  hst ("memcache_store: key='%s', key_len=%d, value_len=%d\n", old_key, old_key_len, size);

  if (verbosity > 1) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d, \n", old_key, old_key_len, size);
  }

  if (size + 1 < MAX_VALUE_LEN) {
    char *key;
    int key_len;

    eat_at (old_key, old_key_len, &key, &key_len);

    if (key_len >= 5 && !strncmp (key, "hints", 5)) {
      int random_tag;

      if (sscanf (key, "hints%d", &random_tag) != 1) {
        RETURN(set, -2);
      }

      if (msg_reinit (MESSAGE(c), size, random_tag) < 0) {
        RETURN(set, -2);
      }
      safe_read_in (&c->In, msg_get_buf (MESSAGE(c)), size);

      RETURN(set, 1);
    }

    if (key_len >= 14 && !strncmp (key, "apps_exception", 14)) {
      int user_id, cur_add;
      if (sscanf (key, "apps_exception%d%n", &user_id, &cur_add) != 1 || user_id <= 0 || key[cur_add]) {
        RETURN(set, -2);
      }

      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      if (verbosity > 1) {
        fprintf (stderr, "add apps exception %d %s\n", user_id, buf);
      }

      int result = do_add_exception (user_id, 41, buf);

      RETURN(set, result);
    }

    if (key_len >= 9 && !strncmp (key, "exception", 9)) {
      int user_id, cur_add, type;
      if (sscanf (key, "exception%d,%d%n", &user_id, &type, &cur_add) != 2 || user_id <= 0 || type <= 0 || type > 255 || key[cur_add]) {
        RETURN(set, -2);
      }

      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      if (verbosity > 1) {
        fprintf (stderr, "add exception %d %d %s\n", user_id, type, buf);
      }

      int result = do_add_exception (user_id, type, buf);
      RETURN(set, result);
    }
  }

  RETURN(set, -2);
}