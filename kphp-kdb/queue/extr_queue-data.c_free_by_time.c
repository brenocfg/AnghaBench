#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int ref_cnt; TYPE_1__* ev_first; } ;
typedef  TYPE_2__ queue ;
struct TYPE_8__ {char* name; int timeout; struct TYPE_8__* next_time; int /*<<< orphan*/  lock; TYPE_2__* q; } ;
typedef  TYPE_3__ qkey ;
struct TYPE_6__ {int ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int GET_TIME_ID (int) ; 
 int MAX_TIME_GAP ; 
 int TIME_TABLE_RATIO_EXP ; 
 size_t TIME_TABLE_SIZE ; 
 int /*<<< orphan*/  delete_qkey (TYPE_3__*) ; 
 int /*<<< orphan*/  events_memory ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keys_memory ; 
 size_t last_del_time ; 
 int /*<<< orphan*/  max_events_memory ; 
 int my_verbosity ; 
 int now ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_3__** time_st ; 

void free_by_time (int mx) {
  int cur_time = get_utime (CLOCK_MONOTONIC);
  int en = GET_TIME_ID(cur_time);
  qkey *st = time_st[last_del_time];

//  fprintf (stderr, "[%ld/%lld]\n", events_memory + keys_memory, max_events_memory);
  while (en - last_del_time > MAX_TIME_GAP || last_del_time - en > TIME_TABLE_SIZE - MAX_TIME_GAP ||
         (mx-- > 0 && last_del_time != en)) {
    if (st->next_time != st) {
      if (my_verbosity > 1) {
        fprintf (stderr, "del entry %p by time (key = %s) gap = %d, timeout = %d, qname = (%p), now = %d, now2 = %d\n", st->next_time, st->next_time->name, en - last_del_time, st->next_time->timeout, st->next_time->q, now, (int)get_utime (CLOCK_MONOTONIC));
        if (st->next_time->q != NULL) {
          queue *q = st->next_time->q;
          fprintf (stderr, "!%s!%d!", q->name, q->ref_cnt);
          if (q->ev_first != NULL) {
            fprintf (stderr, "%d\n", q->ev_first->ref_cnt);
          } else {
            fprintf (stderr, "NULL\n");
          }
        }
      }
      delete_qkey (st->next_time);
    } else {
      if (++last_del_time == TIME_TABLE_SIZE) {
        last_del_time = 0;
      }
      st = time_st[last_del_time];
    }
  }

  en = GET_TIME_ID(cur_time - (2 << TIME_TABLE_RATIO_EXP));
  int cur = last_del_time;
  st = time_st[cur];
  mx = 10000000;
  while (mx-- > 0 && cur != en && events_memory + keys_memory > max_events_memory) {
    qkey *i;
    for (i = time_st[cur]; i->next_time != time_st[cur] && mx > 0; mx--) {
      if (!i->next_time->lock) {
        fprintf (stderr, "del entry %p by memory limit (key = %s) [%ld / %lld]\n", i->next_time, i->next_time->name, events_memory + keys_memory, max_events_memory);
        delete_qkey (i->next_time);
      } else {
        i = i->next_time;
      }
    }
    if (++cur == TIME_TABLE_SIZE) {
      cur = 0;
    }
  }
}