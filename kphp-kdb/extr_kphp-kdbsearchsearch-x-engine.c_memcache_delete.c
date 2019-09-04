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
 int /*<<< orphan*/  delete_queries ; 
 int do_delete_item (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  int owner_id, item_id;

  if (verbosity > 0) {
    fprintf (stderr, "delete \"%s\"\n", key);
  }

  int res = 0;

  switch (*key) {
  case 'i':
    if (sscanf (key, "item%d_%d ", &owner_id, &item_id) == 2 && owner_id && item_id > 0) {
      delete_queries++;
      if (verbosity >= 1) {
      	fprintf (stderr, "delete_item (%d,%d)\n", owner_id, item_id);
      }

      vkprintf (3, "delete: item_id=%lld\n", ((long long) item_id << 32) + (unsigned) owner_id);

      res = do_delete_item (((long long) item_id << 32) + (unsigned) owner_id);
    } else if (sscanf (key, "item%d ", &item_id) == 1 && item_id > 0) {
      delete_queries++;
      vkprintf (1, "delete_item (%d,%d)\n", 0, item_id);
      vkprintf (3, "delete: item_id=%lld\n", (long long)item_id);

      res = do_delete_item (item_id);
    }
    break;
  }
  if (res > 0) {
    write_out (&c->Out, "DELETED\r\n", 9);
  } else {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
  }

  return 0;
}