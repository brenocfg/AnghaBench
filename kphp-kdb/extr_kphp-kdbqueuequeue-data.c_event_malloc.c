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
struct TYPE_5__ {int data_len; int /*<<< orphan*/  created; int /*<<< orphan*/ * next; scalar_t__ ref_cnt; } ;
typedef  TYPE_1__ event ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dl_get_memory_used () ; 
 TYPE_1__* dl_malloc (size_t) ; 
 int /*<<< orphan*/  events_cnt ; 
 int /*<<< orphan*/  events_created ; 
 int /*<<< orphan*/  events_memory ; 
 size_t get_event_size_d (int) ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 

event *event_malloc (int data_len) {
  size_t l = get_event_size_d (data_len);

  events_created++;
  events_cnt++;


  events_memory -= dl_get_memory_used();
  event *e = dl_malloc (l);
  events_memory += dl_get_memory_used();

  assert (e);

  e->data_len = data_len;
  e->ref_cnt = 0;
  e->next = NULL;

  e->created = get_utime (CLOCK_MONOTONIC);

  return e;
}