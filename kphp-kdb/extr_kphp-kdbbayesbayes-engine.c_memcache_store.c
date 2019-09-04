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
 int /*<<< orphan*/  BYS_MSG (struct connection*) ; 
 int /*<<< orphan*/  INIT ; 
 int MAX_VALUE_LEN ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 char* buf ; 
 int do_black_list_add (char*) ; 
 int do_black_list_delete (char*) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* msg_get_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_reinit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*) ; 
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

    //set("current_text{$random_tag}", "$text")
    if (key_len >= 12 && !strncmp (key, "current_text", 12)) {
      int random_tag;
      if (sscanf (key, "current_text%d", &random_tag) != 1) {
        RETURN(set, -2);
      }

      if (verbosity > 1) {
        fprintf (stderr, "current_text %d\n", random_tag);
      }

      if (msg_reinit (BYS_MSG (c), size, random_tag) < 0) {
        RETURN(set, -2); // not_enough memory
      }
      safe_read_in (&c->In, msg_get_buf (BYS_MSG (c)), size);

      RETURN(set, 1);
    }

    if (key_len >= 14 && !strncmp (key, "add_black_list", 14)) {
      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      if (verbosity > 1) {
        fprintf (stderr, "add_black_list %s\n", buf);
      }

      int result = do_black_list_add (buf);
      RETURN(set, result);
    }

    if (key_len >= 17 && !strncmp (key, "delete_black_list", 17)) {
      safe_read_in (&c->In, buf, size);
      buf[size] = 0;

      if (verbosity > 1) {
        fprintf (stderr, "delete_black_list %s\n", buf);
      }

      int result = do_black_list_delete (buf);
      RETURN(set, result);
    }
  }

  RETURN(set, -2);
}