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
 int /*<<< orphan*/  auth_timereset ; 
 scalar_t__ authdecryptions ; 
 scalar_t__ authencryptions ; 
 scalar_t__ authkeylookups ; 
 scalar_t__ authkeynotfound ; 
 scalar_t__ authkeyuncached ; 
 int /*<<< orphan*/  current_time ; 

void
reset_auth_stats(void)
{
	authkeylookups = 0;
	authkeynotfound = 0;
	authencryptions = 0;
	authdecryptions = 0;
	authkeyuncached = 0;
	auth_timereset = current_time;
}