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
 int /*<<< orphan*/  ADD_OPER (int) ; 
 int /*<<< orphan*/  cmd_delete ; 
 int /*<<< orphan*/  del_entry (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int get_entry (char const*,int,long long) ; 
 long long get_hash (char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  if (verbosity > 0) {
    fprintf (stderr, "memcache_delete: key='%s'\n", key);
  }
  cmd_delete++;

  long long key_hash = get_hash (key, key_len);
  int x = get_entry (key, key_len, key_hash);

  ADD_OPER (3);

  if (x != -1) {
    del_entry (x);
    write_out (&c->Out, "DELETED\r\n", 9);
    return 0;
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}