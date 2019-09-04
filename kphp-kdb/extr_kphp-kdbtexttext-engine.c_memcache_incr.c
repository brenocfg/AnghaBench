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
 int do_decr_flags (int,int,long long) ; 
 int do_incr_flags (int,int,long long) ; 
 int do_incr_value (int,int,int,long long) ; 
 int do_incr_value_long (int,int,int,long long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,long long) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int get_message_value (int,int,int,int,long long*) ; 
 int sprintf (char*,char*,long long) ; 
 int sscanf (char const*,char*,int*,int*,...) ; 
 char* stats_buff ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_incr (struct connection *c, int op, const char *key, int key_len, long long arg) {
  int user_id, local_id, res;
  if (verbosity > 1) {
    fprintf (stderr, "memcache_incr: op=%d, key='%s', val=%lld\n", op, key, arg);
  }

  free_tmp_buffers (c);

  if (sscanf (key, "flags%d_%d", &user_id, &local_id) >= 2 && user_id && local_id > 0) {
    if (op) {
      res = do_decr_flags (user_id, local_id, arg);
    } else {
      res = do_incr_flags (user_id, local_id, arg);
    }
    if (res == -2) {
      write_out (&c->Out, "4294967295\r\n", 12);
      return 0;
    } else if (res >= 0) {
      write_out (&c->Out, stats_buff, sprintf (stats_buff, "%d\r\n", res));
      return 0;
    }
  }

  if (key_len >= 5 && !strncmp (key, "extra", 5)) {
    int local_id, value_id;
    if (sscanf (key, "extra%d_%d:%d", &user_id, &local_id, &value_id) == 3 && user_id && local_id > 0 && (unsigned) value_id < 8) {
      res = do_incr_value (user_id, local_id, value_id, op ? -arg : arg);
      if (res <= 0) {
        write_out (&c->Out, "NOT_FOUND\r\n", 11);
        return 0;
      } else {
        long long nres;
        res = get_message_value (user_id, local_id, value_id, -1, &nres);
        if (res == -2) {
          write_out (&c->Out, "-2147483648\r\n", 13);
          return 0;
        } else if (res <= 0) {
          write_out (&c->Out, "NOT_FOUND\r\n", 11);
          return 0;
        }
        write_out (&c->Out, stats_buff, sprintf (stats_buff, "%d\r\n", (int) nres));
        return 0;
      }
    }
  }

  if (key_len >= 5 && !strncmp (key, "Extra", 5)) {
    int local_id, value_id;
    if (sscanf (key, "Extra%d_%d:%d", &user_id, &local_id, &value_id) == 3 && user_id && local_id > 0 && value_id >= 8 && value_id < 12) {
      res = do_incr_value_long (user_id, local_id, value_id, op ? -arg : arg);
      if (res <= 0) {
        write_out (&c->Out, "NOT_FOUND\r\n", 11);
        return 0;
      } else {
        long long nres;
        res = get_message_value (user_id, local_id, value_id, -1, &nres);
        if (res == -2) {
          write_out (&c->Out, "-9223372036854775808\r\n", 22);
          return 0;
        } else if (res <= 0) {
          write_out (&c->Out, "NOT_FOUND\r\n", 11);
          return 0;
        }
        write_out (&c->Out, stats_buff, sprintf (stats_buff, "%lld\r\n", nres));
        return 0;
      }
    }
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}