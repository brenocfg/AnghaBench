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
typedef  int /*<<< orphan*/  event_log_cb ;

/* Variables and functions */
 int /*<<< orphan*/  log_fn ; 

void
event_set_log_callback(event_log_cb cb)
{
	log_fn = cb;
}