#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  In; } ;
struct TYPE_3__ {int data_len; char* key; int key_len; long long key_hash; int flags; int exp_time; scalar_t__* data; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_OPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int MAX_VALUE_LEN ; 
 int SEC_IN_MONTH ; 
 int /*<<< orphan*/  add_entry (int) ; 
 int /*<<< orphan*/  add_entry_time (int) ; 
 int /*<<< orphan*/  add_entry_used (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmd_set ; 
 int /*<<< orphan*/  del_entry_time (int) ; 
 int /*<<< orphan*/  del_entry_used (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_entry (char const*,int,long long) ; 
 TYPE_1__* get_entry_ptr (int) ; 
 long long get_hash (char const*,int) ; 
 int get_new_entry () ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int mct_add ; 
 int mct_replace ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ now ; 
 int read_in (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int* stats_now ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_items ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  zzfree (scalar_t__*,int) ; 
 void* zzmalloc (int) ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  cmd_set++;

  if (delay == 0) {
    delay = SEC_IN_MONTH;
  } else if (delay > SEC_IN_MONTH) {
    delay -= now;
    if (delay > SEC_IN_MONTH) {
      delay = SEC_IN_MONTH;
    }
  }

  if (delay < 0) {
    return -2;
  }

  delay += get_utime (CLOCK_MONOTONIC);

  if (verbosity > 0) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d, flags = %d, exp_time = %d\n", key, key_len, size, flags, delay);
  }

  if (size < MAX_VALUE_LEN) {
    long long key_hash = get_hash (key, key_len);
    int x = get_entry (key, key_len, key_hash);

    ADD_OPER (0);
#ifdef HISTORY
    stats_now[4] += size;
#endif

    hash_entry_t *entry;

    if (x != -1) {
      if (op == mct_add) {
        return -2;
      }

      if (verbosity > 0) {
        fprintf (stderr, "found old entry x = %d\n", x);
      }
      entry = get_entry_ptr (x);

      zzfree (entry->data, entry->data_len + 1);

      del_entry_used (x);
      del_entry_time (x);
    } else {
      if (op == mct_replace) {
        return -2;
      }

      total_items++;

      x = get_new_entry ();

      if (verbosity > 0) {
        fprintf (stderr, "created new entry x = %d\n", x);
      }

      entry = get_entry_ptr (x);

      char *k;
      k = zzmalloc (key_len + 1);
      memcpy (k, key, key_len);
      k[key_len] = 0;

      entry->key = k;
      entry->key_len = key_len;
      entry->key_hash = key_hash;

      add_entry (x);
    }

    entry->data = zzmalloc (size + 1);
    assert (read_in (&c->In, entry->data, size) == size);
    entry->data[size] = 0;

    entry->data_len = size;
    entry->flags = flags;
    entry->exp_time = delay;

    add_entry_used (x);
    add_entry_time (x);

    return 1;
  }

  return -2;
}