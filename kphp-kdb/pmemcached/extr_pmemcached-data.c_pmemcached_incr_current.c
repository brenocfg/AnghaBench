#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int data_len; char* data; int delay; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__ data; TYPE_1__* hash_entry; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {long long accum_value; } ;

/* Variables and functions */
 TYPE_3__* current_cache ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  on_value_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmct_set ; 
 int pmemcached_store_current (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int verbosity ; 

int pmemcached_incr_current (long long arg) {
  if (current_cache->data.data_len == -1) {
    return -1;
  }
  on_value_change (current_cache->key, current_cache->key_len);

  if (current_cache->data.data_len == -2) {
    if (current_cache->hash_entry) {
      current_cache->hash_entry->accum_value += arg;
    } else {
      pmemcached_store_current (pmct_set, 0, -2, 0, -1);
      current_cache->hash_entry->accum_value = arg;
    }
    return 0;
  }

  unsigned long long val = 0;
  int i, f = 1;

  for (i = 0; i < current_cache->data.data_len && f; i++) {
    if ('0' <= current_cache->data.data[i] && current_cache->data.data[i] <= '9') {
      val = val * 10 + current_cache->data.data[i] - '0';
    } else {
      f = 0;
    }
  }

  if (f == 0) {
    val = 0;
  }

  val+=arg;

  char buff[30];
  sprintf (buff, "%llu", val);

  int len = strlen (buff);

  if (verbosity >= 4) {
    fprintf (stderr, "new value is %s\n", buff);
  }

  return pmemcached_store_current (pmct_set, buff, len, current_cache->data.flags, current_cache->data.delay);
}