#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int timeout; struct TYPE_4__* next_time; struct TYPE_4__* prev_time; } ;
typedef  TYPE_1__ wkey ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 size_t GET_TIME_ID (int) ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int max (scalar_t__,int) ; 
 TYPE_1__** time_st ; 

inline void add_entry_time (wkey *entry, int timeout) {
  int new_timeout = max (get_utime (CLOCK_MONOTONIC) + timeout, entry->timeout);

  entry->timeout = new_timeout;

  wkey *f = time_st[GET_TIME_ID (new_timeout)];
  wkey *y = f->prev_time;

  entry->next_time = f;
  f->prev_time = entry;

  entry->prev_time = y;
  y->next_time = entry;
}