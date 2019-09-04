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
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int exec_delete (struct connection*,char*,int) ; 
 scalar_t__ memcache_wait (struct connection*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  c->flags &= ~C_INTIMEOUT;
  char *new_key;
  int new_len;

  eat_at (key, key_len, &new_key, &new_len);

  int res = exec_delete (c, new_key, new_len);

  if (res == -2 && memcache_wait (c)) {
    return 0;
  }

  if (res > 0) {
    write_out (&c->Out, "DELETED\r\n", 9);
  } else {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
  }
  return 0;
}