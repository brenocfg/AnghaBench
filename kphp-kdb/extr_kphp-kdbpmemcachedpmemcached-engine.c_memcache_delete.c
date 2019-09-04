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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_INTIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_disabled ; 
 int /*<<< orphan*/  cmd_delete ; 
 int do_pmemcached_delete (char const*,int) ; 
 int do_pmemcached_preload (char const*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcache_wait (struct connection*) ; 
 scalar_t__ protected_mode ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  if (binlog_disabled == 1) {
    return 0;
  }
  if (protected_mode) {
    return 0;
  }
  c->flags &= ~C_INTIMEOUT;

  if (verbosity >= 3) {
    fprintf (stderr, "memcache_delete: key='%s'\n", key);
  }
  cmd_delete++;

  if (do_pmemcached_preload (key, key_len, 1) == -2) {
    if (!memcache_wait (c)) {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
    }
    return 0;
  }
  int x = do_pmemcached_delete (key, key_len);
  assert (x != -2);

  if (x != -1) {
    write_out (&c->Out, "DELETED\r\n", 9);
    return 0;
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}