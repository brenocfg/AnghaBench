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
 int /*<<< orphan*/  current_time ; 
 scalar_t__ handler_calls ; 
 scalar_t__ handler_pkts ; 
 int /*<<< orphan*/  io_timereset ; 
 scalar_t__ packets_dropped ; 
 scalar_t__ packets_ignored ; 
 scalar_t__ packets_notsent ; 
 scalar_t__ packets_received ; 
 scalar_t__ packets_sent ; 

void
io_clr_stats(void)
{
	packets_dropped = 0;
	packets_ignored = 0;
	packets_received = 0;
	packets_sent = 0;
	packets_notsent = 0;

	handler_calls = 0;
	handler_pkts = 0;
	io_timereset = current_time;
}