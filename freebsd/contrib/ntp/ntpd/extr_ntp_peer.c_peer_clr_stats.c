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
 scalar_t__ assocpeer_calls ; 
 int /*<<< orphan*/  current_time ; 
 scalar_t__ findpeer_calls ; 
 scalar_t__ peer_allocations ; 
 scalar_t__ peer_demobilizations ; 
 int /*<<< orphan*/  peer_timereset ; 

void
peer_clr_stats(void)
{
	findpeer_calls = 0;
	assocpeer_calls = 0;
	peer_allocations = 0;
	peer_demobilizations = 0;
	peer_timereset = current_time;
}