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
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  events_cnt ; 
 int /*<<< orphan*/  events_memory ; 
 size_t get_event_size (int /*<<< orphan*/ *) ; 

void event_free (event *e) {
  size_t l = get_event_size (e);

  events_cnt--;

  events_memory -= dl_get_memory_used();
  dl_free (e, l);
  events_memory += dl_get_memory_used();
}