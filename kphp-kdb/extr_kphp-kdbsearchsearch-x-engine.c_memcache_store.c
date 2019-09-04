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
struct connection {int dummy; } ;

/* Variables and functions */
 int MAX_RATES ; 
 int do_store (struct connection*,long long,int,int,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,int,int,int,int) ; 
 int get_sorting_mode (char const) ; 
 int /*<<< orphan*/  minor_update_queries ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_queries ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,...) ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  int rate, rate2, owner_id, item_id;
  long long ritem_id = 0;
  int cur_op;
  int ok = 0;
  int no_reply = 0;

  if (verbosity > 0) {
    fprintf (stderr, "mc_store: op=%d, key=\"%s\", flags=%d, expire=%d, bytes=%d, noreply=%d\n", op, key, flags, delay, size, no_reply);
  }

  owner_id = 0;
  if (size >= 65536) {
    return -2;
  }
  if (op == 1 && size >= 0 && size < 65536 &&
     ((sscanf (key, "item%d#%d,%d ", &item_id, &rate, &rate2) == 3 && item_id > 0)
      || (sscanf (key, "item%d_%d#%d,%d ", &owner_id, &item_id, &rate, &rate2) == 4 && owner_id && item_id > 0)
    )) {

    update_queries++;

    ritem_id = owner_id ? ((long long) item_id << 32) + (unsigned) owner_id : item_id;

    vkprintf (3, "store: item_id=%016llx\n", ritem_id);

    cur_op = 0;
    ok = 1;
  }

  if (!ok && op == 1 && size >= 0 && size < 256) {
    int act = 0;
    owner_id = 0;
    if (sscanf (key+1, "ate%d_%d ", &owner_id, &item_id) == 2 && owner_id && item_id > 0) {
      act = 1;
    } else if (sscanf (key+1, "ate%d ", &item_id) == 1 && item_id > 0) {
      owner_id = 0;
      act = 1;
    }

    if (act) {
      int p = get_sorting_mode (*key);

      vkprintf (4, "p = %d, *key=%c\n", p, *key);

      act = (p >= 0 && p < MAX_RATES) ? (p+1) : 0;
    }

    if (!act && sscanf (key, "rates%d_%d ", &owner_id, &item_id) == 2 && owner_id && item_id > 0) {
      act = MAX_RATES+1;
    } else if (sscanf (key, "rates%d ", &item_id) == 1 && item_id > 0) {
      owner_id = 0;
      act = MAX_RATES+1;
    }

    if (!act && sscanf (key, "hash%d_%d ", &owner_id, &item_id) == 2 && owner_id && item_id > 0) {
      act = MAX_RATES+2;
    } else if (sscanf (key, "hash%d ", &item_id) == 1 && item_id > 0) {
      owner_id = 0;
      act = MAX_RATES+2;
    }

    if (act) {
      minor_update_queries++;
      rate = 0;
      rate2 = 0;
      cur_op = act;
      ritem_id = owner_id ? ((long long) item_id << 32) + (unsigned) owner_id : item_id;
      ok = 1;
    }
  }

  vkprintf (3, "store: item_id=%016llx, cur_op = %d\n", ritem_id, cur_op);

  int res = 0;
  if (ok) {
    res = do_store (c, ritem_id, rate, rate2, cur_op, size);
  }

  if (res > 0) {
    return 1;
  } else {
    return 0;
  }
}