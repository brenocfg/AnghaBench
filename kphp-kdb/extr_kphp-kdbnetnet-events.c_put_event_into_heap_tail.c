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
struct TYPE_4__ {scalar_t__ timestamp; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 scalar_t__ ev_timestamp ; 
 int put_event_into_heap (TYPE_1__*) ; 

int put_event_into_heap_tail (event_t *ev, int ts_delta) {
  ev->timestamp = ev_timestamp + ts_delta;
  return put_event_into_heap (ev);
}