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
 int MAX_RATES ; 
 int /*<<< orphan*/  delete_hash_queries ; 
 int delete_hash_query_items ; 
 int /*<<< orphan*/  delete_queries ; 
 int do_delete_item (int) ; 
 int do_delete_items_with_hash (long long) ; 
 int do_reset_all_rates (int) ; 
 int get_sorting_mode (char) ; 
 int sscanf (char const*,char*,...) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  int owner_id, item_id;
  vkprintf (1, "delete \"%s\"\n", key);
  int res = 0;
  long long h = 0;
  char d, e;
  if (sscanf (key, "itemswithhash%llx", &h) == 1) {
    delete_hash_queries++;
    res = do_delete_items_with_hash (h);
    delete_hash_query_items += res;
  } else if (sscanf (key, "item%d_%d ", &owner_id, &item_id) == 2 && owner_id && item_id > 0) {
    delete_queries++;
    vkprintf (1, "delete_item (%d,%d)\n", owner_id, item_id);
    vkprintf (3, "delete: item_id=%lld\n", ((long long) item_id << 32) + (unsigned) owner_id);
    res = do_delete_item (((long long) item_id << 32) + (unsigned) owner_id);
  } else if (sscanf (key, "item%d ", &item_id) == 1 && item_id > 0) {
    delete_queries++;
    vkprintf (1, "delete_item (%d,%d)\n", 0, item_id);
    vkprintf (3, "delete: item_id=%lld\n", (long long) item_id);
    res = do_delete_item (item_id);
  } else if (sscanf (key, "reset_all_%cate%c", &d, &e) == 2 && e == 's') {
    int p = get_sorting_mode (d);
    if (p >= 0 && p < MAX_RATES) {
      delete_queries++;
      res = do_reset_all_rates (p);
    }
  }
  if (res > 0) {
    write_out (&c->Out, "DELETED\r\n", 9);
  } else {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
  }
  return 0;
}