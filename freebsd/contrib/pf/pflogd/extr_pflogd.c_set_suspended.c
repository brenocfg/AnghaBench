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
 int /*<<< orphan*/  cur_snaplen ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  interface ; 
 int /*<<< orphan*/  setproctitle (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int suspended ; 

void
set_suspended(int s)
{
	if (suspended == s)
		return;

	suspended = s;
	setproctitle("[%s] -s %d -i %s -f %s",
	    suspended ? "suspended" : "running",
	    cur_snaplen, interface, filename);
}