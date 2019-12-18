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

/* Variables and functions */
 int /*<<< orphan*/  aborted ; 
 int /*<<< orphan*/  add_fill_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_active_slot ; 
 int /*<<< orphan*/  fill_active_slots () ; 
 int /*<<< orphan*/  finish_all_active_slots () ; 
 int is_running_queue ; 
 scalar_t__ request_queue_head ; 

__attribute__((used)) static void run_request_queue(void)
{
#ifdef USE_CURL_MULTI
	is_running_queue = 1;
	fill_active_slots();
	add_fill_function(NULL, fill_active_slot);
#endif
	do {
		finish_all_active_slots();
#ifdef USE_CURL_MULTI
		fill_active_slots();
#endif
	} while (request_queue_head && !aborted);

#ifdef USE_CURL_MULTI
	is_running_queue = 0;
#endif
}