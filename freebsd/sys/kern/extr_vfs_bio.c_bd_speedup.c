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
 int bd_request ; 
 int bd_speedupreq ; 
 int /*<<< orphan*/  bdlock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
bd_speedup(void)
{
	int needwake;

	mtx_lock(&bdlock);
	needwake = 0;
	if (bd_speedupreq == 0 || bd_request == 0)
		needwake = 1;
	bd_speedupreq = 1;
	bd_request = 1;
	if (needwake)
		wakeup(&bd_request);
	mtx_unlock(&bdlock);
}