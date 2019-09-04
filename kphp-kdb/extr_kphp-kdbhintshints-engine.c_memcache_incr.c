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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_increment_user_object_rating (int,int,long long,long long,int) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 scalar_t__ fading ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,long long) ; 
 int /*<<< orphan*/  history_q_add (char*,int) ; 
 int /*<<< orphan*/  incr ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_incr (struct connection *c, int op, const char *old_key, int old_key_len, long long arg) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_incr: op=%d, key='%s', val=%lld\n", op, old_key, arg);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  history_q_add (key, 2);

  if (op == 1) {
    if (fading) {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
      RETURN(incr, 0);
    }
    arg *= -1;
  }

  if (arg > (1ll << 30)) {
    arg = (1ll << 30);
  } else if (arg < -(1ll << 30)) {
    arg = -(1ll << 30);
  }

  //Изменение рейтинга объекта
  //increment ("user_object{$user_id},{$type}:{$object_id}", {$cnt})</code>
  if (key_len >= 11 && !strncmp (key, "user_object", 11)) {
    int user_id, type;
    long long object_id;
    int object_id2;
    int add = -1, add2 = -1;

    int t = sscanf (key + 11, "%d,%d:%lld%n_%d%n", &user_id, &type, &object_id, &add, &object_id2, &add2);
    if (t == 3 || t == 4) {
      if (t == 4) {
        if ((object_id != user_id && object_id2 != user_id) || add2 == -1) {
          RETURN(incr, 0);
        }
        if (object_id == user_id) {
          object_id = object_id2;
        }
        add = add2;
      }
      int num;
      if (sscanf (key + 11 + add, "*%d", &num) != 1) {
        num = 0;
      }

      int x = do_increment_user_object_rating (user_id, type, object_id, arg, num);
      if (x) {
        write_out (&c->Out, "1\r\n", 3);
        RETURN(incr, 0);
      }
    }
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  RETURN(incr, 0);
}