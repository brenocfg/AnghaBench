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
 int /*<<< orphan*/  ctltimereset ; 
 int /*<<< orphan*/  current_time ; 
 scalar_t__ numasyncmsgs ; 
 scalar_t__ numctlbadoffset ; 
 scalar_t__ numctlbadop ; 
 scalar_t__ numctlbadpkts ; 
 scalar_t__ numctlbadversion ; 
 scalar_t__ numctldatatooshort ; 
 scalar_t__ numctlerrors ; 
 scalar_t__ numctlfrags ; 
 scalar_t__ numctlinputerr ; 
 scalar_t__ numctlinputfrag ; 
 scalar_t__ numctlinputresp ; 
 scalar_t__ numctlreq ; 
 scalar_t__ numctlresponses ; 
 scalar_t__ numctltooshort ; 

void
ctl_clr_stats(void)
{
	ctltimereset = current_time;
	numctlreq = 0;
	numctlbadpkts = 0;
	numctlresponses = 0;
	numctlfrags = 0;
	numctlerrors = 0;
	numctlfrags = 0;
	numctltooshort = 0;
	numctlinputresp = 0;
	numctlinputfrag = 0;
	numctlinputerr = 0;
	numctlbadoffset = 0;
	numctlbadversion = 0;
	numctldatatooshort = 0;
	numctlbadop = 0;
	numasyncmsgs = 0;
}