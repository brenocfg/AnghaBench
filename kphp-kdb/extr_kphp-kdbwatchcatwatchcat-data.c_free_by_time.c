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
struct TYPE_5__ {int x; struct TYPE_5__* next_time; } ;
typedef  TYPE_1__ wkey ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int GET_TIME_ID (int /*<<< orphan*/ ) ; 
 int MAX_TIME_GAP ; 
 size_t TIME_TABLE_SIZE ; 
 int /*<<< orphan*/  del_wkey (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 size_t last_del_time ; 
 int my_verbosity ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__** time_st ; 

void free_by_time (int mx) {
  int en = GET_TIME_ID (get_utime (CLOCK_MONOTONIC));
  wkey *st = time_st[last_del_time];

  while (en - last_del_time > MAX_TIME_GAP || last_del_time - en > TIME_TABLE_SIZE - MAX_TIME_GAP ||
         (mx-- && last_del_time != en)) {
    if (st->next_time != st) {
      if (my_verbosity > 1) {
        fprintf (stderr, "del entry %p by time (key = %d) gap = %d\n", st->next_time, st->next_time->x, en - last_del_time);
      }
      del_wkey (st->next_time);
    } else {
      if (++last_del_time == TIME_TABLE_SIZE) {
        last_del_time = 0;
      }
      st = time_st[last_del_time];
    }
  }
}