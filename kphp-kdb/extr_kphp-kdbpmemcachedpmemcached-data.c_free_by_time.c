#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* key; int /*<<< orphan*/  key_len; struct TYPE_5__* next_time; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int GET_TIME_ID (int /*<<< orphan*/ ) ; 
 int MAX_TIME_GAP ; 
 size_t TIME_TABLE_SIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  do_pmemcached_delete (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* entry_buffer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  get_double_time_since_epoch () ; 
 size_t last_del_time ; 
 int /*<<< orphan*/  stderr ; 
 int* time_st ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

void free_by_time (int mx) {
  vkprintf (4, "free_by_time: mx = %d\n", mx);
  int en = GET_TIME_ID (get_double_time_since_epoch()),
      st = time_st[last_del_time];

  while (en - last_del_time > MAX_TIME_GAP || last_del_time - en > TIME_TABLE_SIZE - MAX_TIME_GAP || 
         (mx-- && last_del_time != en)) {
    hash_entry_t  *entry_time = &entry_buffer[st];
    assert (entry_time->next_time);
    if (entry_time->next_time != entry_time) {
      if (verbosity >= 4) {
        fprintf(stderr, "del entry %p by time(key = %s) gap = %d\n", entry_time->next_time, entry_time->next_time->key, en - last_del_time);
      }
      do_pmemcached_delete (entry_time->next_time->key, entry_time->next_time->key_len);
    } else {
      if (++last_del_time == TIME_TABLE_SIZE) {
        last_del_time = 0;
      }
      st = time_st[last_del_time];
    }
  }
}