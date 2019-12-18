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
 int do_add_answer (int,int,int,int,char*) ; 
 int do_set_mark (int,int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  hst (char*,char const*,int,int) ; 
 char* msg_get_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_reinit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  safe_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

int memcache_store (struct connection *c, int op, const char *old_key, int old_key_len, int flags, int delay, int size) {
  INIT;

  hst ("memcache_store: key='%s', key_len=%d, value_len=%d\n", old_key, old_key_len, size);

  if (unlikely (size >= MAX_VALUE_LEN)) {
    RETURN (set, -2);
  }

  char *key;
  int key_len;
  eat_at (old_key, old_key_len, &key, &key_len);

  //set("question{$random_tag}", "$text")
  if (key_len >= 8 && !strncmp (key, "question", 8)) {
    int random_tag;
    if (sscanf (key + 8, "%d", &random_tag) != 1) {
      RETURN (set, -2);
    }

    if (msg_reinit (MESSAGE (c), size, random_tag) < 0) {
      RETURN (set, -2);
    }
    safe_read_in (&c->In, msg_get_buf (MESSAGE (c)), size);

    RETURN (set, 1);
  }

  if (key_len >= 6 && !strncmp (key, "answer", 6)) {
    int user_id, agent_id, mark, cur;
    safe_read_in (&c->In, buf, size);

    if (sscanf (key + 6, "%d,%d,%d%n", &user_id, &agent_id, &mark, &cur) < 3 || key[6 + cur]) {
      RETURN (set, 0);
    }

    int res = do_add_answer (user_id, agent_id, mark, size, buf);
    RETURN (set, res);
  }

  //get("mark{$question_id}", {$new_mark});
  if (key_len >= 4 && !strncmp (key, "mark", 4)) {
    int user_id, mark, cur;
    safe_read_in (&c->In, buf, size);

    if (sscanf (key + 4, "%d%n", &user_id, &cur) < 1 || key[4 + cur] || sscanf (buf, "%d%n", &mark, &cur) < 1 || buf[cur]) {
      RETURN (set, 0);
    }

    int res = do_set_mark (user_id, mark);
    RETURN (set, res);
  }

  RETURN (set, -2);
}