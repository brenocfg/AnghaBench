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
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  eq_total ; 
 long long events_memory ; 
 long long get_event_size (int /*<<< orphan*/ *) ; 

void event_free (event *e) {
  if (e == NULL) {
    return;
  }

  long long size = get_event_size (e);
  events_memory -= size;

  eq_total--;
//  dbg ("event_free (addr = %p) (size = %lld)\n", e, size);
  dl_free (e, size);
}