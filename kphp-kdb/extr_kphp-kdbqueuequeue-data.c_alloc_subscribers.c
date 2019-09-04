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
typedef  int /*<<< orphan*/  subscribers ;

/* Variables and functions */
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/ * dl_malloc0 (int) ; 
 int /*<<< orphan*/  subscribers_cnt ; 
 int /*<<< orphan*/  subscribers_memory ; 

subscribers *alloc_subscribers (void) {
  subscribers_cnt++;

  subscribers_memory -= dl_get_memory_used();
  subscribers *res = dl_malloc0 (sizeof (subscribers));
  subscribers_memory += dl_get_memory_used();

  return res;
}